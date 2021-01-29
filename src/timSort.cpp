#include "../include/sortalgos.hpp"

#include <algorithm>
#include <iostream>
#include <stack>

#define MIN_RUN  32
#define MAX_RUN  64

using namespace std;

using RevRegIter = std::reverse_iterator<RegIterator>;

class Chunk
{
private:
    pair<RegIterator, RegIterator> _info;
public:
    Chunk(RegIterator begin, RegIterator end):
        _info { begin, end }
    {}

    RegIterator begin()
    {
        return this->_info.first;
    }

	RevRegIter rend()
	{
		return RevRegIter(this->begin());
	}

    RegIterator end()
    {
        return this->_info.second;
    }

	RevRegIter rbegin()
	{
		return RevRegIter(this->end());
	}

    size_t size()
    {
        return (this->end() - this->begin());
    }
};

/*Insertion Sort: */
static void insertionSort(RegIterator inicio, RegIterator fim, compRegFunc comp)    
{ 
    for (RegIterator i = inicio + 1; i < fim; i++) {
        for (RegIterator j = i; j > inicio && comp(*j, *(j-1)) < 0; j--) {
            std::swap(*j, *(j-1));
        }
    }
} 

/*Calcula tamanho das Runs: */
static RegIterator calculaFimRun(RegIterator inicio, RegIterator limiteSuperior)
{
    RegIterator fimrun = inicio;
    RegIterator a = inicio;
    size_t totalDeElementos = limiteSuperior - inicio;

    if (totalDeElementos < 2) {
        return inicio;
    }

    if ((a + 1)->cases() >= a->cases()) {
        while ((a + 1)->cases() >= a->cases()) {
            a++;
            /*se o tamanho atual n é maior q o max da run 64*/
            if (a - inicio >= MAX_RUN || a >= limiteSuperior) {
                return fimrun;
            }
            fimrun++;
        }
    } else {
        while ((a + 1)->cases() <= a->cases()) {
            a++;
            if( a - inicio >= MAX_RUN || a >= limiteSuperior  ) {
                return fimrun;
            }
            fimrun++;
        }
        reverse(a, fimrun + 1);
    }

    /*se o tamanho atual n é menor q o min da run 32*/
    if (fimrun - a < MIN_RUN) {
        fimrun = (inicio + MIN_RUN < limiteSuperior)
            ? (inicio + MIN_RUN) : limiteSuperior;
    }
    return fimrun;
}

static Chunk merge(Chunk& run1, Chunk& run2 ,compRegFunc comp)
{   
    Chunk *leftRun;
    Chunk *rightRun;

    if (run1.begin() < run2.begin()) {
        leftRun = &run1;
        rightRun = &run2;
    } else {
        leftRun = &run2;
        rightRun = &run1;
    }

	Chunk resultado(leftRun->begin(), rightRun->end());

	std::vector<Registro> merged;

	auto lrunit = leftRun->begin();
	auto rrunit = rightRun->begin();
	while (lrunit != leftRun->end() && rrunit != rightRun->end()) {
		merged.push_back(std::move(
			(comp(*rrunit, *lrunit) < 0) ? (*rrunit++) : (*lrunit++)
		));
	}

	while (lrunit != leftRun->end()) {
		merged.push_back(std::move(
			*lrunit++
		));
	}

	while (rrunit != rightRun->end()) {
		merged.push_back(std::move(
			*rrunit++
		));
	}

	std::copy(
		move_iterator<RegIterator>(merged.begin()),
		move_iterator<RegIterator>(merged.end()),
		resultado.begin()
	);
	return resultado;
}

/*Faz o merge das Runs atuais em ordem crescente, e mantém a estabilidade */
static void ajustaSegmentoDeRunsDinamicamente(stack<Chunk>& pilhaDeRuns, compRegFunc comp)
{
    if (pilhaDeRuns.size() >= 3) {
        bool segmentoOrdenado = false;
		std::cerr << "Entrando no loop infinito\n";
		while (!segmentoOrdenado && pilhaDeRuns.size() > 2) {
            //a nomenclatura representa o segmento de 3 atual
            Chunk topo = std::move(pilhaDeRuns.top());
			pilhaDeRuns.pop();
            Chunk meio = std::move(pilhaDeRuns.top());
			pilhaDeRuns.pop();
            Chunk fundo = std::move(pilhaDeRuns.top());
			pilhaDeRuns.pop();

			std::cerr << "Tamanho do fundo: " << fundo.size() << '\n';
			std::cerr << "Tamanho do meio: " << meio.size() << '\n';
			std::cerr << "Tamanho do topo: " << topo.size() << '\n';
            if (fundo.size() > topo.size() + meio.size()) {
                if (meio.size() > fundo.size()) {
                    segmentoOrdenado = true;
                } else {
                    pilhaDeRuns.push(std::move(merge(fundo, meio, comp)));
					pilhaDeRuns.push(std::move(topo));
                }
            } else if (fundo.size() >= topo.size()) {
				pilhaDeRuns.push(std::move(fundo));
                pilhaDeRuns.push(std::move(merge(meio, topo, comp)));
            } else if (fundo.size() < topo.size()) {
                pilhaDeRuns.push(std::move(merge(meio, fundo, comp)));
				pilhaDeRuns.push(std::move(topo));
            }
        }
		std::cerr << "Saindo do loop infinito\n";
    }
}

void timSort(RegIterator begin, RegIterator end, compRegFunc comp)
{
    stack<Chunk> pilhaDeRuns;

    for (RegIterator lo = begin, ho ; lo < end; lo = ho) { 
        ho = calculaFimRun(lo, end);
        insertionSort(lo, ho, comp); 
        pilhaDeRuns.push({lo,ho});
        ajustaSegmentoDeRunsDinamicamente(pilhaDeRuns, comp);
    }
}
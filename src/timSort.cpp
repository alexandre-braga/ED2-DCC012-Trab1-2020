#include "../include/sortalgos.hpp"

#include <algorithm>
#include <iostream>
#include <stack>
#include <cassert>

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

static int _comparacoes;
static int _trocas;

RegIterator findInsertionPos(RegIterator begin, RegIterator end, const Registro& val, compRegFunc comp)
{
	RegIterator it;
	auto count = distance(end, begin);

	while (count > 0) {
		auto step = count / 2;
		it = begin;
		it += step;

		if (comp(val, *it) < 0) {
			count = step;
		} else {
			begin = ++it;
			count -= step;
		}
	}
	return begin;
}

void binInsertion(RegIterator begin, RegIterator end, Registro val, compRegFunc func)
{
	RegIterator insertionPos = findInsertionPos(begin, end, val, func);
	RevRegIter rend(insertionPos);
	RevRegIter rbegin(end);
	RevRegIter it = rbegin;
	RevRegIter next = it + 1;

	while (next < rend) {
		*it = *next;
		it = next++;
	}
	*insertionPos = std::move(val);
} 

/*Calcula tamanho das Runs: */
static RegIterator calculaFimRun(RegIterator inicio, RegIterator limiteSuperior, compRegFunc comp)
{
    RegIterator fimrun = inicio;
    RegIterator a = inicio;
    size_t totalDeElementos = limiteSuperior - inicio;

    if (totalDeElementos < MIN_RUN) {
        return limiteSuperior;
    }

    if (++_comparacoes && comp(*(a + 1), *a) >= 0) {

        while (++_comparacoes && comp(*(a + 1), *a) >= 0) {
            a++;
            if (a - inicio >= MAX_RUN || a >= limiteSuperior) {
                return fimrun;
            }
            fimrun++;
        }

        while (a < limiteSuperior && (a - inicio) < MIN_RUN) {
            a++;
            fimrun++;
            if (++_comparacoes && comp(*(a + 1), *a) < 0) {
                binInsertion(inicio, (a + 1), std::move(*(a + 1)), comp);
            }
        }

    } else {

        while (++_comparacoes && comp(*(a + 1), *a) <= 0) {
            a++;
            if (a - inicio >= MAX_RUN || a >= limiteSuperior) {
                return fimrun;
            }
            fimrun++;
        }

        while (a < limiteSuperior && (a - inicio) < MIN_RUN) {
            auto reverseComp = [comp](const Registro& r1, const Registro& r2)-> int {
                return -comp(r1, r2);
            };

            if (++_comparacoes && comp(*(a + 1), *a) < 0) {
                binInsertion(inicio, (a + 1), std::move(*(a + 1)), reverseComp);
            }
            a++;
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
    //assert(leftRun->end() == rightRun->begin());

	Chunk resultado(leftRun->begin(), rightRun->end());

	std::vector<Registro> merged;

	auto lrunit = leftRun->begin();
	auto rrunit = rightRun->begin();
	while (lrunit != leftRun->end() && rrunit != rightRun->end()) {
		_comparacoes++;
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
    
    //for(RegIterator it = resultado.begin(); it != resultado.end(); it++){
    //    cerr << *it << '\n';
    //}
    //cerr << "\n\n";
    _trocas += resultado.size() * 2;
	return resultado;
}

void mergeFinal(stack<Chunk>& pilhaDeRuns, compRegFunc comp){
    while(pilhaDeRuns.size() > 1){
        Chunk a = pilhaDeRuns.top();
        pilhaDeRuns.pop();
        Chunk b = pilhaDeRuns.top();
        pilhaDeRuns.pop();
        Chunk c = merge(a, b, comp);
        pilhaDeRuns.push(c);
        //for(RegIterator it = c.begin(); it != c.end(); it++){
        //    cerr << *it << '\n';
        //}
        //cerr << "\n\n";
    }
}

/*Faz o merge das Runs atuais em ordem crescente, e mantém a estabilidade */
static void ajustaSegmentoDeRunsDinamicamente(stack<Chunk>& pilhaDeRuns, compRegFunc comp)
{
    //std::cerr << "Entrando no loop infinito\n";
    while (pilhaDeRuns.size() > 2) {
        //a nomenclatura representa o segmento de 3 atual
        Chunk z = std::move(pilhaDeRuns.top());
        pilhaDeRuns.pop();
        Chunk y = std::move(pilhaDeRuns.top());
        pilhaDeRuns.pop();
        Chunk x = std::move(pilhaDeRuns.top());
        pilhaDeRuns.pop();

        /*
        std::cerr << "Tamanho do x: " << x.size() << '\n';
        std::cerr << "Tamanho do y: " << y.size() << '\n';
        std::cerr << "Tamanho do z: " << z.size() << '\n';
        */
        // x > y + z   E    y > z
        if (x.size() > y.size() + z.size() && y.size() > z.size()) {
            mergeFinal(pilhaDeRuns, comp);
        } else if (x.size() > y.size() + z.size()) {
			pilhaDeRuns.push(std::move(x));
            pilhaDeRuns.push(merge(y, z, comp));
        } else if (x.size() < y.size() + z.size()) {
			if (z.size() < x.size()) {
                pilhaDeRuns.push(std::move(x));
                pilhaDeRuns.push(merge(y, z, comp));
			} else {
                pilhaDeRuns.push(merge(x, y, comp));
                pilhaDeRuns.push(std::move(z));
			}
        }
    }
    //std::cerr << "Saindo do loop infinito\n";
}

void timSort(RegIterator begin, RegIterator end, int &comparacoes, int &trocas, compRegFunc comp)
{
    stack<Chunk> pilhaDeRuns;
    _comparacoes = _trocas = 0;
    for (RegIterator lo = begin, ho ; lo < end; lo = ho) { 
        ho = calculaFimRun(lo, end, comp);
        pilhaDeRuns.push({lo,ho});
        ajustaSegmentoDeRunsDinamicamente(pilhaDeRuns, comp);
        mergeFinal(pilhaDeRuns, comp);
        comparacoes = _comparacoes;
        trocas = _trocas;
    }
}
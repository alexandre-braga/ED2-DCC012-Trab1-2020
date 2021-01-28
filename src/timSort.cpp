#include "../include/sortalgos.hpp"

#include <algorithm>
#include <iostream>

#define MIN_RUN  32
#define MAX_RUN  64

using namespace std;

class Chunk
{
private:
    pair<RegIterator, RegIterator> _info;
public:
    Chunk(RegIterator inicio, RegIterator fim):
        _info { inicio, fim }
    {}

    const RegIterator& inicio() const
    {
        return this->_info.first;
    }

    const RegIterator& fim() const
    {
        return this->_info.second;
    }

    size_t tamanho() const
    {
        return (this->fim() - this->inicio());
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

    if (totalDeElementos <= 1) {
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

/*Merge Sort:*/
#define min(x,y) (((x) < (y)) ? (x) : (y))

static Chunk merge(Chunk& leftRun, Chunk& rightRun ,compRegFunc comp)
{                              
    return Chunk(leftRun.inicio(), rightRun.fim());
//     size_t leftRunLen = leftRun.first - leftRun.second;
//     size_t rightRunLen = rightRun.first - rightRun.second;
//     unique_ptr<Registro> temp = new Registro[min(leftRunLen,rightRunLen)];
//     size_t tamanhoTemp;

//     //Aloca um vetor temp com len da menor Run, e move os elementos da menor Run pra temp
//     if (rightRunLen < leftRunLen) {
//         tamanhoTemp = rightRunLen;
//         temp = new Registro[tamanhoTemp];
//         for(size_t i = 0; i < tamanhoTemp; i++) {
//             temp[i] = std::move(*(rightRun.first + (i)));
//         }
//         for(size_t j = leftRun.second; j > leftRun.first; j--) {
//             vet[j]+=4
//         }
//     } else {
//         tamanhoTemp = leftRunLen;
//         temp = new Registro[tamanhoTemp];
//         for(size_t i = 0; i < tamanhoTemp; i++)
//             temp[i] = std::move(*(leftRun.first + (i)));
//     }

//     pont do leftRun = min(pont do temp, pont do runmaior){
//         pont do selecionado++;
//         pont do leftRun++;
//     }

//     while (vetit1 != vet1.end() && vetit2 != vet2.end()) {
//         if (comp(*vetit1, *vetit2) <= 0) {
//             merged.push_back(*vetit1++);
//         } else {
//             merged.push_back(*vetit2++);
//         }
//     }
//     while (vetit1 != vet1.end()) {
//         merged.push_back(*vetit1++);
//     }
//     while (vetit2 != vet2.end()) {
//         merged.push_back(*vetit2++);
//     }
//     return merged;
}

/*Faz o merge das Runs atuais em ordem crescente, e mantém a estabilidade */
static void ajustaSegmentoDeRunsDinamicamente(vector<Chunk>& pilhaDeRuns, compRegFunc comp)
{
    if (pilhaDeRuns.size() >= 3) {
        bool segmentoOrdenado = false;
        while (!segmentoOrdenado && pilhaDeRuns.size() > 3) {
            //a nomenclatura representa o segmento de 3 atual
            Chunk& topo = pilhaDeRuns[pilhaDeRuns.size() - 1];
            Chunk& meio = pilhaDeRuns[pilhaDeRuns.size() - 2];
            Chunk& fundo = pilhaDeRuns[pilhaDeRuns.size() - 3];

            if (topo.tamanho() > fundo.tamanho() + meio.tamanho()) {
                if (meio.tamanho() > fundo.tamanho()) {
                    segmentoOrdenado = true;
                } else {
                    meio = merge(fundo, meio, comp);
                }
            } else if (fundo.tamanho() >= topo.tamanho()) {
                meio = merge(meio, topo, comp);
            } else if (fundo.tamanho() < topo.tamanho()) {
                meio = merge(meio, fundo, comp);
            }
        }
    }
}

void timSort(RegIterator begin, RegIterator end, compRegFunc comp)
{
    std::vector<Chunk> pilhaDeRuns;

    for (RegIterator lo = begin, ho ; lo < end; lo = ho) { 
        ho = calculaFimRun(lo, end);
        insertionSort(lo, ho, comp); 
        pilhaDeRuns.push_back({lo,ho});
        ajustaSegmentoDeRunsDinamicamente(pilhaDeRuns, comp);
    }
}
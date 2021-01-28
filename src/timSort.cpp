#include "../include/timSort.hpp"
#include <algorithm>
#include <iostream>

#define MIN_RUN  32
#define MAX_RUN  64

using namespace std;
using RegIterator = vector<Registro>::iterator;

/*Insertion Sort: */
void insertionSort(RegIterator inicio, RegIterator fim, compRegFunc comp)    
{ 
    for (RegIterator i = inicio + 1; i < fim; i++) {
        for (RegIterator j = i; j > inicio && comp(*j, *(j-1)) < 0; j--) {
            std::swap(*j, *(j-1));
        }
    }
} 

/*Calcula tamanho das Runs: */
RegIterator calculaFimRun(RegIterator inicio, RegIterator limiteSuperior)
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

vector<Registro> merge(pair<RegIterator,RegIterator>& leftRun, pair<RegIterator,RegIterator>& rightRun, vector<Registro>& vet, compRegFunc comp)
{                              
    size_t leftRunLen = leftRun.first - leftRun.second;
    size_t rightRunLen = rightRun.first - rightRun.second;
    unique_ptr<Registro> temp = new Registro[min(leftRunLen,rightRunLen)];
    size_t tamanhoTemp;

    //Aloca um vetor temp com len da menor Run, e move os elementos da menor Run pra temp
    if (rightRunLen < leftRunLen) {
        tamanhoTemp = rightRunLen;
        temp = new Registro[tamanhoTemp];
        for(size_t i = 0; i < tamanhoTemp; i++) {
            temp[i] = std::move(*(rightRun.first + (i)));
        }
        for(size_t j = leftRun.second; j > leftRun.first; j--) {
            vet[j]+=4
        }
    } else {
        tamanhoTemp = leftRunLen;
        temp = new Registro[tamanhoTemp];
        for(size_t i = 0; i < tamanhoTemp; i++)
            temp[i] = std::move(*(leftRun.first + (i)));
    }

    pont do leftRun = min(pont do temp, pont do runmaior){
        pont do selecionado++;
        pont do leftRun++;
    }

    while (vetit1 != vet1.end() && vetit2 != vet2.end()) {
        if (comp(*vetit1, *vetit2) <= 0) {
            merged.push_back(*vetit1++);
        } else {
            merged.push_back(*vetit2++);
        }
    }
    while (vetit1 != vet1.end()) {
        merged.push_back(*vetit1++);
    }
    while (vetit2 != vet2.end()) {
        merged.push_back(*vetit2++);
    }
    return merged;
}

/*Faz o merge das Runs atuais em ordem crescente, e mantém a estabilidade */
void ajustaSegmentoDeRunsDinamicamente (vector<pair<RegIterator,RegIterator>>& pilhaDeRuns, vector<Registro>& vet, compRegFunc comp)
{
    if (pilhaDeRuns.size() >= 3) {
        bool segmentoOrdenado = false;
        while (!segmentoOrdenado && pilhaDeRuns.size() > 3) {
            //a nomenclatura representa o segmento de 3 atual
            std::<pair<RegIterator,RegIterator>>& topo = pilhaDeRuns[pilhaDeRuns.size() - 1];
            std::<pair<RegIterator,RegIterator>>& meio = pilhaDeRuns[pilhaDeRuns.size() - 2];
            std::<pair<RegIterator,RegIterator>>& fundo = pilhaDeRuns[pilhaDeRuns.size() - 3];
            size_t topoLen = topo.first - topo.second;
            size_t meioLen = meio.first - meio.second;
            size_t fundoLen = fundo.first - fundo.second;

            if (topoLen > fundoLen + meioLen) {
                if (meioLen > fundoLen) {
                    segmentoOrdenado = true;
                } else {
                    meio = merge(fundo, meio, comp);
                }
            } else if (fundoLen >= topoLen) {
                meio = merge(meio, topo, comp);
            } else if (fundoLen < topoLen) {
                meio = merge(meio, fundo, comp);
            }
        }
    }
}

void timSort(RegIterator begin, RegIterator end, compRegFunc comp)
{
    std::vector<std::pair<RegIterator,RegIterator>> pilhaDeRuns;

    for (RegIterator lo = begin, ho ; lo < end; lo = ho) { 
        ho = calculaFimRun(lo, end);
        insertionSort(lo, ho, comp); 
        pilhaDeRuns.push_back({lo,ho});
        ajustaSegmentoDeRunsDinamicamente(pilhaDeRuns, vet, comp);
    }
}
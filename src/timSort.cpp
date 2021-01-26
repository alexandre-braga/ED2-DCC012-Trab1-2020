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
    for(RegIterator i = inicio + 1; i < fim; i++){
        for(RegIterator j = i; j > inicio && comp(*j, *(j-1)) < 0; j--){
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

    if(totalDeElementos <= 1){
        return inicio;
    }

    if((a + 1)->cases() >= a->cases()){
        while((a + 1)->cases() >= a->cases()){
            a++;
            /*se o tamanho atual n é maior q o max da run 64*/
            if( a - inicio >= MAX_RUN || a >= limiteSuperior  )
                return fimrun;
            fimrun++;
        }
    }
    else{
        while((a + 1)->cases() <= a->cases()){
            a++;
            /*se o tamanho atual n é maior q o max da run 64*/
            if( a - inicio >= MAX_RUN || a >= limiteSuperior  )
                return fimrun;
            fimrun++;
        }
        reverse(a, fimrun + 1);
    }

    /*se o tamanho atual n é menor q o min da run 32*/
    if(fimrun - a < MIN_RUN) 
        fimrun = (inicio + MIN_RUN < limiteSuperior) ? inicio + MIN_RUN : limiteSuperior;
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
    if(rightRunLen < leftRunLen){
        tamanhoTemp = rightRunLen;
        temp = new Registro[tamanhoTemp];
        for(size_t i = 0; i < tamanhoTemp; i++)
            temp[i] = std::move(*(rightRun.first + (i)));
    }
    else{
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

/*Faz o merge das Runs em ordem crescente, e mantém a estabilidade */
void ajustaPilhaDeRuns (vector<pair<RegIterator,RegIterator>>& pilhaDeRuns, vector<Registro>& vet, compRegFunc comp)
{
    while (pilhaDeRuns.size() >= 3) { //segmentation fault here
        std::<pair<RegIterator,RegIterator>>& primeiro = pilhaDeRuns[pilhaDeRuns.size() - 1];
        std::<pair<RegIterator,RegIterator>>& segundo = pilhaDeRuns[pilhaDeRuns.size() - 2];
        std::<pair<RegIterator,RegIterator>>& terceiro = pilhaDeRuns[pilhaDeRuns.size() - 3];
        size_t primeiroLen = primeiro.first - primeiro.second;
        size_t segundoLen = segundo.first - segundo.second;
        size_t terceiroLen = terceiro.first - terceiro.second;

        if (terceiroLen >= primeiroLen + segundoLen) {
            if (primeiroLen > segundoLen)
               segundo = merge(primeiro, segundo, comp);
            else
                break; //loop here
        }
        //a unica dif do do indiano: e q n uso min aqui uso 2 if
        else if (primeiroLen > terceiroLen)
            segundo = merge(segundo, terceiro, comp);
        else if (primeiroLen < terceiroLen)
            segundo = merge(segundo, primeiro, comp);

    }
    primeiro = merge(primeiro, segundo, comp);

    std::swap(vet,pilhaDeRuns[fim]);
}

void timSort(RegIterator begin, RegIterator end, compRegFunc comp)
{
    cerr << "inicio timsort\n";
    std::vector<std::pair<RegIterator,RegIterator>> pilhaDeRuns;

    for (RegIterator lo = begin, ho ; lo < end; lo = ho){ 
        ho = calculaFimRun(lo, end);
        if(ho > end)
            cout << "Error ho > end\n";
        insertionSort(lo, ho, comp); 
        pilhaDeRuns.push_back({lo,ho});
    }
    //ajustaPilhaDeRuns(pilhaDeRuns, vet, comp);
}
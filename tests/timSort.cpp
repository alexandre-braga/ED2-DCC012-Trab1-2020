#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "../include/Registro.hpp"
 
const int MIN_RUN = 64;

/*Merge Sort:*/


/*Insertion Sort: */
void insertionSort(int vet[], int inicio, int fim) 
{ 
    for (int i = inicio + 1; i <= fim; i++) 
    { 
        int pivo = vet[i]; 
        int j = i - 1; 
        while (j >= inicio && vet[j] > pivo) 
        { 
            vet[j+1] = vet[j]; 
            j--; 
        } 
        vet[j+1] = pivo; 
    } 
} 

/*Mantém a runs em tamanho crescente enquanto desce a pilha:*/
enquanto (o tamanho das runs >=2){
    se(run(n) > run(n-1)+run(n-2){
        se(run (n-2) > run (n-1))
           merge( run (n-2), run (n-1) )
        se nao
           break
    })
    se nao{
        merge( run (n-1), menor entre(run(n-2), run(n)) )
    }
}

while (pilhaDeRuns.size >= 2){
    if(pilhaDeRuns[]){

    }
    else{
        mergeSort(vet[])
    }
    
}


/*Começando a partir da posição do elemento atual, procure o Run (um sub-vetor ordenado) no vetor de entrada. Por definição o Run será pelo menos o elemento atual e o próximo (pois formará um vetor ordenado, seja crescente ou decrescente), sendo que a composição de mais elementos no Run dependerá da forma como os elementos estão organizados. O próximo elemento é considerado se ao considerá-lo no Run atual, o Run continue ordenado. Se o Run final está ordenado de forma decrescente, os elementos são "reordenados" em uma ordem crescente (por meio de um algoritmo  simples de inversão de vetor).
-wikipedia
*/

void verificaFimRun(int vet[], int i){
    int fimrum = 0;
    if(vet[i+1]>=vet[i])
        while(vet[i]<=vet[i+1]){
            i++
            if(vet[i] == NULL){
                return fimrum;
            }
            fimrun++;
        }
        if(fimrum < MIN_RUN)
            fimrun+=MIN_RUN-fimrum;
        return fimrum;
    else
        while(vet[i]>=vet[i+1]){
           i++
           if(vet[i] == NULL){
                return fimrum;
            }
           fimrun++;
        }
        std::reverse(vet.a, vet.fimrun);
        if(fimrum < MIN_RUN)
           fimrum+=MIN_RUN-fimrum;
        return fimrum;
}



void timSort(vector<Registro>& vet, int(*comp)(const Registro&, const Registro&)){
    /*Organiza as RUNS e faz o InsertionSort nelas:*/
    for (int i = 0, int j = verificaFimRun(vet,i); i < n; i+=j){
        insertionSort(vet, i, j);
    }

    /*Faz o Merge para as RUNS já em ordem crescente de tamanho*/
    n = vet.size;
    int RUNAux = MIN_RUN;
    while RUNAux < n{
        for(i = 0; i < n; i+=2*RUNAux){
            mergeSort(vet,)
        }
        RUNAux = 2*RUNAux
    }
    
}

/*Pro MERGE simplificado:*/
int RUNAux = MIN_RUN
while RUNAux < tamArray
    um for (com i no inicio do vetor; i menor que o tamanho do vetor; e tendo como passo duas RUN) 
        array[i até i+RUNAux] = Merge(array[i até i+RUNAux], array[i+RUNAux até i+2*RUNAux] )
    RUNAux = 2*RUNAux

  
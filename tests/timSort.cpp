#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
 
const int MIN_RUN = 64;


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
        Começando a partir da posição do elemento atual, procure o Run (um sub-vetor ordenado) no vetor de entrada. Por definição o Run será pelo menos o elemento atual e o próximo (pois formará um vetor ordenado, seja crescente ou decrescente), sendo que a composição de mais elementos no Run dependerá da forma como os elementos estão organizados. O próximo elemento é considerado se ao considerá-lo no Run atual, o Run continue ordenado. Se o Run final está ordenado de forma decrescente, os elementos são "reordenados" em uma ordem crescente (por meio de um algoritmo  simples de inversão de vetor).

void verificaRun(, int a, int b){
}

void timSort(){
    /*Organiza as RUNS:*/
    stack<int> pilhaDeRuns;
    n = vet.size;
    for (int i = 0; i < n; i+=RUN) 
        insertionSort(vet, i, min((i+RUN-1),(n-1)));
        //Insere na pilha os indices das runs
        pilhaDeRuns.push(i);
    /*Faz o Merge para as RUNS já em ordem crescente de tamanho*/
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
  
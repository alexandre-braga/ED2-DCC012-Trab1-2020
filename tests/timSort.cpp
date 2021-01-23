#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "../include/Registro.hpp"
 
const int MIN_RUN = 64;


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


/*Merge Sort:*/




/*Isto é feito da seguinte maneira:
Cria-se uma pair stack <Posição do primeiro elemento do Run>-<Tamanho do Run>.
Insere-se o Run atual à pair stack.
Avalia se deve ser feito o merge.
Avaliação: Sejam X, Y e Z os 3 primeiros Runs da pair stack; X > Y + Z e Y > Z. Se uma das duas condições não é satisfeita, então é feito o merge do Run Y com o Run de menor tamanho entre X e Z.
Para qualquer Run que não tenha sido considerado, basta tomá-lo e ir para o passo 2 até que reste apenas um Run na pilha (que é o vetor final já ordenado).
-wikipedia
*/


/*Mantém a runs em tamanho crescente enquanto desce a pilha:*/

/*
z > x + y 
y > x

x
yy
zzzz
*/

void ajustaPilhaDeRuns (vector<vector<int>> pilhaDeRuns){
    while (pilhaDeRuns.size >= 2){
    for(i=1; i+1<=n; i++){
        std::vector<int> a = pilhaDeRuns[i-1];
        std::vector<int> b = pilhaDeRuns[i];
        std::vector<int> c = pilhaDeRuns[i+1];
        int x = a.size;
        int y = b.size;
        int z = c.size;
        if(z > x + y){
            if(x > y)
                merge(pilhaDeRuns[i-1], pilhaDeRuns[i]);
            else
                break;
        }
        else{
            merge(pilhaDeRuns[i],min(pilhaDeRuns[i-1], pilhaDeRuns[i+1]);
        }
    }
}





void timSort(vector<Registro>& vet, int(*comp)(const Registro&, const Registro&)){
    /*Organiza as RUNS e faz o InsertionSort nelas:*/
    for (int i = 0, int j = verificaFimRun(vet,i); i < n; i+=j){
        vector<vector<int>> pilhaDeRuns;
        pilhaDeRuns.push_back(insertionSort(vet, i, j);); 
    }
    /*Faz o Merge para as RUNS enquanto deixa elas em ordem crescente de tamanho*/
    ajustaPilhaDeRuns(pilhaDeRuns);

    /*Faz o Merge para as RUNS já em ordem crescente de tamanho - elas não estão:
    n = vet.size;
    int RUNAux = MIN_RUN;
    while RUNAux < n{
        for(i = 0; i < n; i+=2*RUNAux){
            vet[i até i+RUNAux] = Merge(vet[i até i+RUNAux], vet[i+RUNAux até i+2*RUNAux] )
        }
        RUNAux = 2*RUNAux
    }*/
}
  
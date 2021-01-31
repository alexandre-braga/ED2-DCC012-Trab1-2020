#include <iostream>
#include <vector>

#include "../include/sortalgos.hpp"

/*
int indicePivo(std::vector<Registro>& vet) {
    int iVet = 0;
    int fVet = vet.size() - 1;
    int mVet = (iVet + fVet)/2;
    if (vet[iVet].cases() < vet[mVet].cases()) {
        if (vet[iVet].cases() < vet[fVet].cases())
            return iVet;
    } else if (vet[mVet].cases() < vet[fVet].cases()) {
        return mVet;
    } return fVet;
}
*/
/*
// Algoritmo 1
void quickSort(std::vector<Registro>& vet, int iVet, int fVet, 
int &comparacoes, int &trocas, compRegFunc comp)
{
    //particionamento do vetor
    if (iVet >= fVet) {
        return;
    }
    
    std::swap(vet[iVet], vet[indicePivo(vet)]);
//    trocas++;

    int ultimo = iVet;
    for (int i = iVet + 1; i <= fVet; ++i) {
        if(vet[i].cases() < vet[iVet].cases()) {
            std::swap(vet[i], vet[++ultimo]);
//            trocas++;
        }
//        comparacoes++;
    }
//    comparacoes++;

    std::swap(vet[iVet], vet[ultimo]);
//    trocas++;

    //chamadas recursivas
    quickSort(vet, iVet, ultimo - 1, comparacoes, trocas, comp);
    quickSort(vet, ultimo + 1, fVet, comparacoes, trocas, comp);
}
*/

/*
// Algoritmo 2
int part(std::vector<Registro>& vet, int p, int q, 
int &comparacoes, int &trocas, compRegFunc comp) {
    Registro pivo = vet[q];
    int i = p-1;

    for(int j = p; j < q; j++)
    {
        comparacoes++;
    	if(comp(vet[j], pivo) < 0)
        {
            i++;
            std::swap(vet[i], vet[j]);
            trocas++;
        }
    }
    std::swap(vet[i+1], vet[q]);
    trocas++;
    return i+1;
}

void quickSort(std::vector<Registro>& vet, int p, int r, 
int &comparacoes, int &trocas, compRegFunc comp) {
    if(p < r) {
        int q = part(vet, p, r, comparacoes, trocas, comp);
        quickSort(vet, p, q-1, comparacoes, trocas, comp);
        quickSort(vet, q+1, r, comparacoes, trocas, comp);
    }
}
*/

// Algoritmo 3
void quickSort(std::vector<Registro>& vet, int iVet, int fVet, int &comparacoes, int &trocas, compRegFunc comp)
{
    if (fVet - iVet < 0)
        return;
    //particionamento do vetor
    int pivo = vet[((iVet + fVet)/2)].cases();
    int i = iVet;
    int j = fVet;
    int k = iVet;
    while (i <= j) {
        if (++comparacoes && (vet[i].cases() < pivo)) {
            std::swap(vet[i], vet[k]);
            trocas++;
            k++;
            i++;
        } else if (++comparacoes && (vet[i].cases() > pivo)) {
            while (++comparacoes && (vet[j].cases() >= vet[i].cases())) {
                j--;
            }
            std::swap(vet[i], vet[j]);
            trocas++;
            j--;
        } else {
            i++;
        }
    }

    //chamadas recursivas
    quickSort(vet, iVet, k - 1, comparacoes, trocas, comp);
    quickSort(vet, j + 1, fVet, comparacoes, trocas, comp);
}

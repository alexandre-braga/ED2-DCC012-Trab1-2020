#include <iostream>
#include <vector>

#include "../include/sortalgos.hpp"

void quickSort(std::vector<Registro>& vet, int iVet, int fVet)
{
    //particionamento do vetor
    if (iVet >= fVet) {
        return;
    } 
    std::swap(vet[iVet], vet[((iVet + fVet)/2)]);
    int ultimo = iVet;
    for (int i = iVet + 1; i <= fVet; ++i) {
        if (vet[i].cases() < vet[iVet].cases()) {
            std::swap(vet[i], vet[++ultimo]);
        }
    }
    std::swap(vet[iVet], vet[ultimo]);
    //chamadas recursivas
    quickSort(vet, iVet, ultimo - 1);
    quickSort(vet, ultimo + 1, fVet);
}
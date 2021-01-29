#include <iostream>
#include <vector>

#include "../include/Registro.hpp"

void quickSort(std::vector<Registro>& vet, int iVet, int fVet) {
    //particionamento do vetor
    Registro pivo = vet[(iVet + fVet)/2]; //pega o elemento do meio -- mudar caso necessario
    int i = iVet;
    int j = fVet;
    while (i <= j) {
        while (vet[i].cases() < pivo.cases()) {
            i++;
        }
        while (vet[j].cases() > pivo.cases()) {
            j--;
        }
        if (i <= j) {
            std::swap(vet[i], vet[j]);
            i++;
            j++;
        }
    }
    //chamadas recursivas
    if (fVet - iVet > 0) {
        quickSort(vet, iVet, j - 1);
        quickSort(vet, j + 1, fVet);
    }
}
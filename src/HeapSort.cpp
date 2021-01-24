#include <iostream>
#include <vector>

#include "../include/Registro.hpp"
#include "../include/HeapSort.hpp"

#define parent(__i) (((__i) - 1)) / 2)

#define left(__i) ((__i) * 2 + 1)

#define right(__i) ((__i) * 2 + 2)

void maxHeap(std::vector<Registro>& vet, int i, int n, int &comparacoes, int &trocas, 
                    int(*comp)(const Registro&, const Registro&))
{
    int l = left(i);
    int r = right(i);
    int m;

    if (l < n && comp(vet[l], vet[i]) > 0) {
        m = l;
        comparacoes++;
    } else {
        m = i;
        comparacoes++;
    }

    if (r < n && comp(vet[r], vet[m]) > 0) {
        m = r;
        comparacoes++;
    }

    if (m != i) {
        std::swap(vet[i], vet[m]);
        trocas++;
        maxHeap(vet, m, n, comparacoes, trocas, comp);
    }
}

void buildMaxHeap(std::vector<Registro>& vet, int &comparacoes, int &trocas, 
                    int(*comp)(const Registro&, const Registro&))
{
    for (int i = vet.size()/2 - 1; i >= 0; i--) {
        maxHeap(vet, i, vet.size(), comparacoes, trocas, comp);
    }
}

void heapSort(std::vector<Registro>& vet, int &comparacoes, int &trocas, 
                    int(*comp)(const Registro&, const Registro&))
{
    buildMaxHeap(vet, comparacoes, trocas, comp);
    for (int i = vet.size() - 1; i >= 1; i--) {
        std::swap(vet[0], vet[i]);
        maxHeap(vet, 0, i, comparacoes, trocas, comp);
    }
}

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#include "../include/Registro.hpp"

using namespace std;

#define parent(__i) (((__i) - 1)) / 2)

#define left(__i) ((__i) * 2 + 1)

#define right(__i) ((__i) * 2 + 2)

void maxHeap(vector<Registro>& vet, int i, int n, int(*comp)(const Registro&, const Registro&))
{
    int l = left(i);
    int r = right(i);
    int m;

    if (l < n && comp(vet[l], vet[i]) > 0) {
        m = l;
    } else {
        m = i;
    }

    if (r < n && comp(vet[r], vet[m]) > 0) {
        m = r;
    }
    if (m != i) {
        std::swap(vet[i], vet[m]);
        maxHeap(vet, m, n, comp);
    }
}

void buildMaxHeap(vector<Registro>& vet, int(*comp)(const Registro&, const Registro&))
{
    for (int i = vet.size()/2 - 1; i >= 0; i--) {
        maxHeap(vet, i, vet.size(), comp);
    }
}

void heapSort(vector<Registro>& vet, int(*comp)(const Registro&, const Registro&))
{
    buildMaxHeap(vet, comp);

    for (int i = vet.size() - 1; i >= 1; i--) {
        std::swap(vet[0], vet[i]);
        maxHeap(vet, 0, i, comp);
    }
}

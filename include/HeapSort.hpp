#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <iostream>
#include <vector>

void maxHeap(std::vector<Registro>& vet, int i, int n, int &comparacoes, int &trocas, 
int(*comp)(const Registro&, const Registro&));

void buildMaxHeap(std::vector<Registro>& vet, int &comparacoes, int &trocas, 
int(*comp)(const Registro&, const Registro&));

void heapSort(std::vector<Registro>& vet, int &comparacoes, int &trocas, 
int(*comp)(const Registro&, const Registro&));

#endif /* HEAPSORT_HPP */
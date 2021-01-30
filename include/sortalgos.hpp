#ifndef SORT_ALGOS_HPP
#define SORT_ALGOS_HPP 1

#include <vector>
#include "Registro.hpp"

using RegIterator = std::vector<Registro>::iterator; 
using compRegFunc = int(*)(const Registro&, const Registro&);

void timSort(RegIterator begin, RegIterator end, compRegFunc comp);

void heapSort(std::vector<Registro>& vet, int &comparacoes, int &trocas, compRegFunc comp); 

void quickSort(std::vector<Registro>& vet, int iVet, int fVet, int &comparacoes, int &trocas, compRegFunc comp);

#endif /* SORT_ALGOS_HPP */
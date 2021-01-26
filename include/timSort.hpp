#ifndef TIM_SORT_HPP
#define TIM_SORT_HPP 1

#include <vector>
#include "Registro.hpp"

using RegIterator = std::vector<Registro>::iterator; 
using compRegFunc = int(*)(const Registro&, const Registro&);

void timSort(RegIterator begin, RegIterator end, compRegFunc comp);

#endif /* TIM_SORT_HPP */
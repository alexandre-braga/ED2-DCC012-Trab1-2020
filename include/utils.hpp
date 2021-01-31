#ifndef UTILS_HPP
#define UTILS_HPP 1

#include <vector>
#include "./Registro.hpp"

void calculaTotalDiarios(std::vector<Registro>& vet);

float calculaMedia(float vet[], size_t n);

float calculaMedia(int vet[], size_t n);

float calculaVariancia(float vet[], size_t n, float media);

float calculaVariancia(int vet[], size_t n, float media);

#endif // UTILS_HPP
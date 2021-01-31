#include "../include/utils.hpp"

using namespace std;

void calculaTotalDiarios(std::vector<Registro>& vet)
{
	std::vector<Registro>::reverse_iterator it = vet.rbegin();
	std::vector<Registro>::reverse_iterator next;

	while ((next = it + 1) != vet.rend()) {
		if (it->code() == next->code()) {
			it->setCases(it->cases() - next->cases());
			it->setDeaths(it->deaths() - next->deaths());
		}
		it = next;
	}
}

float calculaMedia(float vet[], size_t n)
{
	float soma = 0.0;
	for(size_t i = 0; i < n; ++i)
		soma += vet[i];
	return soma / n;
}

float calculaMedia(int vet[], size_t n)
{
	float soma = 0.0;
	for(size_t i = 0; i < n; ++i)
		soma += vet[i];
	return soma / n;
}

float calculaVariancia(float vet[], size_t n, float media)
{
	float variancia = 0.0;
	for(size_t i = 0; i < n; ++i)
		variancia += pow(vet[i] - media, 2);
	return variancia / n;
}

float calculaVariancia(int vet[], size_t n, float media)
{
	float variancia = 0.0;
	for(size_t i = 0; i < n; ++i) 
		variancia += pow(vet[i] - media, 2);
	return variancia / n;
}
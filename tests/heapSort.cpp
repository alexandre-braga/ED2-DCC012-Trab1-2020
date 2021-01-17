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

int comp(const Registro& r1, const Registro& r2)
{
	if (r1.state() < r2.state())
		return -1;
    if (r2.state() < r1.state())
		return 1;
    if (r1.city() < r2.city())
		return -1;
	if (r2.city() < r1.city())
		return 1;
    if (r1.date() < r2.date())
		return -1;
	return 1;
}

void calculaTotalDiarios(vector<Registro>& lista)
{
	vector<Registro>::reverse_iterator it = lista.rbegin();
	vector<Registro>::reverse_iterator next;

	while ((next = it + 1) != lista.rend()) {
		if (it->code() == next->code()) {
			it->setCases(it->cases() - next->cases());
		}
		it = next;
	}
}

int main(int argc, char *argv[])
{
	std::vector<Registro> vet;
	Registro r;
	ifstream f;
	ofstream arquivoSaida;

	if (argc < 2) {
		std::cerr << "Nenhum arquivo fornecido\n";
		exit(1);
	}

	arquivoSaida.open("brazil_covid19_cities_processos.csv");
	if (!arquivoSaida.is_open()) {
		std::cerr << "Falha ao abrir o arquivo de saída\n";
		exit(2);
	}
	f.open(*++argv);

	if (f.is_open()) {
		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		while (f >> r) {
			vet.push_back(r);
		}

		heapSort(vet, comp);
		calculaTotalDiarios(vet);

		for (const Registro& r : vet) {
			arquivoSaida << r << '\n';
		}
		
	} else {
		std::cerr << "Erro ao abrir o arquivo `" << *argv << "\n";
		return 2;
	}

	return 0;
}

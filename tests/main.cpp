#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "../include/Registro.hpp"
#include "../include/HeapSort.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2

void calculaTotalDiarios(vector<Registro>& lista)
{
	std::vector<Registro>::reverse_iterator it = lista.rbegin();
	std::vector<Registro>::reverse_iterator next;

	while ((next = it + 1) != lista.rend()) {
		if (it->code() == next->code()) {
			it->setCases(it->cases() - next->cases());
		}
		it = next;
	}
}

int main(int argc, char *argv[])
{
	const char *progname = *argv;

	if (argc < 2) {
		std::cerr << progname << ": nenhum arquivo fornecido\n";
		exit(ERR_NENHUM_ARG);
	}

	while (--argc) {
		std::ifstream f;

		f.open(*++argv);

		if (!f.is_open()) {
			std::cerr << progname << ": falha ao abrir o arquivo `" << *argv << "`\n";
			exit(ERR_FALHA_ARQ);
		}

		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Registro registro;
		std::vector<Registro> arrayRegistros;

		while (f >> registro) {
			arrayRegistros.push_back(registro);
		}
		heapSort(arrayRegistros, Registro::comparaLocalData);
		calculaTotalDiarios(arrayRegistros);

		for (const Registro& registro : arrayRegistros) {
			std::cout << registro << std::endl;
		}

		f.close();
	}
	return 0;
}

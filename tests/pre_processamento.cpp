#include <iostream>
#include <fstream>
#include <limits>

#include "../include/Registro.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2

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

		Registro registro;

		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		while (f >> registro) {
			std::cout << registro;
		}
		f.close();
	}
	return 0;
}

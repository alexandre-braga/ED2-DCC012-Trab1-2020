#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "./include/Registro.hpp"
#include "./include/HeapSort.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2

void calculaTotalDiarios(vector<Registro>& arr)
{
	std::vector<Registro>::reverse_iterator it = arr.rbegin();
	std::vector<Registro>::reverse_iterator next;

	while ((next = it + 1) != arr.rend()) {
		if (it->code() == next->code()) {
			int c = it->cases() - next->cases();
			int d = it->deaths() - next->deaths();
			if(c >= 0) 
				it->setCases(c);
			else
				it->setCases(0);
			if(d >= 0) 
				it->setDeaths(d);
			else
				it->setDeaths(0);
		}
		it = next;
	}
}

void escrevePreProcessado(vector<Registro>& arr, ofstream& file)
{
	file << "date,state,name,code,cases,deaths" << std::endl;
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		file << it->date()   << ",";
		file << it->state()  << ","; 
		file << it->city()   << ",";
		file << it->code()   << ",";
		file << it->cases()  << ",";
		file << it->deaths() << std::endl;
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
		std::ifstream fin;

		fin.open(*++argv);

		if (!fin.is_open()) {
			std::cerr << progname << ": falha ao abrir o arquivo `" << *argv << "`\n";
			exit(ERR_FALHA_ARQ);
		}

		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Registro registro;
		std::vector<Registro> arrayRegistros;

		while (fin >> registro) {
			arrayRegistros.push_back(registro);
		}

		fin.close();

		heapSort(arrayRegistros, Registro::comparaLocalData);
		calculaTotalDiarios(arrayRegistros);

		std::ofstream fout;
		fout.open("brazil_covid19_cities_processado.csv");
		if(!fout.fail()) {
			escrevePreProcessado(arrayRegistros, fout);
		}
		else {
			std::cout << progname << ": falha ao escrever arquivo\n";
		}
		fout.close();
	}

	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

#include "./include/Registro.hpp"
#include "./include/HeapSort.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2
#define M 5 // numero de cojuntos
#define N 5 // numero de registros aleatorios

void calculaTotalDiarios(vector<Registro>& vet)
{
	std::vector<Registro>::reverse_iterator it = vet.rbegin();
	std::vector<Registro>::reverse_iterator next;

	while ((next = it + 1) != vet.rend()) {
		if (it->code() == next->code()) {
			int c = it->cases() - next->cases();
			int d = it->deaths() - next->deaths();
		}
		it = next;
	}
}

void escreverArquivo(vector<Registro>& vet, ofstream& file)
{
	file << "date,state,name,code,cases,deaths" << std::endl;
	for (const auto& r : vet) {
		file << r << '\n';
	}
}

void lerArquivo(std::ifstream& file, vector<Registro>& vet) 
{
	// Ignorar header
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Registro r;
	while (file >> r) {
		vet.push_back(r);
	}
}

std::vector<Registro> nAleatorios(vector<Registro>& vet, unsigned int n)
{
	int limit;
	if(n <= vet.size())
		limit = n;
	else
		limit = vet.size();

	std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, limit); // define the range

	std::vector<Registro> aleatorios;
    for(unsigned int i=0; i < n; ++i)
		aleatorios.push_back(vet[distr(gen)]);

	return aleatorios;
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

		std::vector<Registro> vetRegistros;
		lerArquivo(fin, vetRegistros);
		fin.close();

		// Pre-processamento
		int comparacoes = 0;
		int trocas = 0;
		heapSort(vetRegistros, comparacoes, trocas, Registro::comparaLocalData);
		calculaTotalDiarios(vetRegistros);

		std::ofstream fout;
		fout.open("brazil_covid19_cities_processado.csv");
		if(!fout.fail())
			escreverArquivo(vetRegistros, fout);
		else
			std::cout << progname << ": falha ao escrever arquivo\n";
		
		fout.close();

		std::vector<Registro> vet;
		int arrComp[M * N] = {0};
		int arrTrocas[M * N] = {0};
		
		std::chrono::steady_clock::time_point begin;
		std::chrono::steady_clock::time_point end;
		int arrTempos[M * N];

		int mediasComp[M];
		int mediasTrocas[M];
		float mediasTempos[M];

		// Ordenacao
		int arr[] = {10000, 50000, 100000, 500000, 1000000};
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < N; ++j) {
				std::cout << "N = " << arr[j] << std::endl;
				std::cout << "Comparacoes\tTrocas\tTempo [µs]\n";
				vet = nAleatorios(vetRegistros, arr[j]);

				begin = std::chrono::steady_clock::now();
				heapSort(vetRegistros, arrComp[i * N + j], arrTrocas[i * N + j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				std::cout << arrComp[i * N + j] << "\t" << arrTrocas[i * N + j] << "\t";
				arrTempos[i * N + j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				std::cout << arrTempos[i * N + j] << std::endl;

				/*
				begin = std::chrono::steady_clock::now();
				quickSort(vetRegistros, arrComp[i * N + j], arrTrocas[i * N + j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				std::cout << arrComp[i * N + j] << "\t" << arrTrocas[i * N + j] << "\t";
				arrTempos[i * N + j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				std::cout << arrTempos[i * N + j] << std::endl;
				*/

				/*			
				begin = std::chrono::steady_clock::now();
				timSort(vetRegistros, arrComp[i * N + j], arrTrocas[i * N + j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				std::cout << arrComp[i * N + j] << "\t" << arrTrocas[i * N + j] << "\t";
				arrTempos[i * N + j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				std::cout << arrTempos[i * N + j] << std::endl;
				*/
			}

			// Precisa passar os ponteiros pro primeiro e ultimo elementos do vetor nessa
			// Mas nao to fazendo certo pq tá retornando uns numeros absurdos
			// Vai pegar arr[i * N] ate arr[i * N + N - 1] pq precisa da media de M
			// Exemplo: M = 0 vai pegar de 0 ate N - 1; M = 1 vai pegar de N ate 2N + 1
			// Media de comparacoes
			mediasComp[i] = std::accumulate(&arrComp[i * N], &arrComp[i * N + N - 1], 0) / N;
			// Media de trocas
			mediasTrocas[i] = std::accumulate(&arrTrocas[i * N], &arrTrocas[i * N + N - 1], 0) / N;
			// Media do tempo
			mediasTempos[i] = std::accumulate(&arrTempos[i * N], &arrTempos[i * N + N - 1], 0) / N;
			std::cout << std::endl;
			std::cout << "Media de comparacoes: " << mediasComp[i] << std::endl;
			std::cout << "Media de trocas: " << mediasTrocas[i] << std::endl;
			std::cout << "Tempo medio [µs]: " << mediasTempos[i] << std::endl;
			std::cout << std::endl;
		}
	}

	return 0;
}
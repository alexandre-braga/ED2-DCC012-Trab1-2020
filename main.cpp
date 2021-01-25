#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <cstdio>

#include "./include/Registro.hpp"
#include "./include/HeapSort.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2
#define M 5 // numero de cojuntos
#define N 5 // numero de registros aleatorios

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

void escreverTXT(FILE* file, int arr[], int matrizComp[][M], int matrizTrocas[][M], 
int matrizTempos[][M], int mediasComp[], int mediasTrocas[], int mediasTempos[], 
int stdComp[], int stdTrocas[], int stdTempos[])
{
	
	for(size_t i = 0; i < N; ++i) 
	{
		fprintf(file, "\n%-4s%-11d%-15s%-15s%-15s\n", "N = ", arr[i], "Comparacoes", "Trocas", "Tempo [µs]");
		for(size_t j = 0; j < M; ++j) 
		{
			fprintf(file, "%-15d%-15d%-15d%-15d\n", (int) j, matrizComp[i][j], matrizTrocas[i][j], matrizTempos[i][j]);
		}
		fprintf(file, "%-15s%-15d%-15d%-15d\n", "Media", mediasComp[i], mediasTrocas[i], mediasTempos[i]);
		fprintf(file, "%-15s%-15d%-15d%-15d\n", "std", stdComp[i], stdTrocas[i], stdTempos[i]);
	}
}

void escreverCSV(std::vector<Registro>& vet, std::ofstream& file)
{
	file << "date,state,name,code,cases,deaths" << std::endl;
	for (auto it = vet.begin(); it != vet.end(); ++it) {
		file << it->date()   << ",";
		file << it->state()  << ","; 
		file << it->city()   << ",";
		file << it->code()   << ",";
		file << it->cases()  << ",";
		file << it->deaths() << std::endl;
	}
}

void lerArquivo(std::ifstream& file, std::vector<Registro>& vet) 
{
	// Ignorar header
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Registro r;
	while (file >> r) {
		vet.push_back(r);
	}
}

std::vector<Registro> nAleatorios(std::vector<Registro>& vet, size_t n)
{
	size_t limit;
	if(n <= vet.size())
		limit = n;
	else
		limit = vet.size();

	std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, limit); // define the range

	std::vector<Registro> aleatorios;
    for(size_t i = 0; i < n; ++i)
		aleatorios.push_back(vet[distr(gen)]);

	return aleatorios;
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

int main(int argc, char *argv[])
{
	const char *progname = *argv;

	if (argc < 2) 
	{
		std::cerr << progname << ": nenhum arquivo fornecido\n";
		exit(ERR_NENHUM_ARG);
	}

	while (--argc) 
	{	
		std::ifstream fin;
		fin.open(*++argv);

		if (!fin.is_open()) 
		{
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
			escreverCSV(vetRegistros, fout);
		else
			std::cout << progname << ": falha ao escrever arquivo `brazil_covid19_cities_processado.csv`\n";
		
		fout.close();

		std::vector<Registro> vet;
		int matrizComp[N][M] = {};
		int matrizTrocas[N][M] = {};
		
		std::chrono::steady_clock::time_point begin;
		std::chrono::steady_clock::time_point end;
		int matrizTempos[N][M];

		int mediasComp[N];
		int stdComp[N];
		int mediasTrocas[N];
		int stdTrocas[N];
		int mediasTempos[N];
		int stdTempos[N];

		// Ordenacao
		int arr[] = {10000, 50000, 100000, 500000, 1000000};
		for(size_t i = 0; i < N; ++i) {
			for(size_t j = 0; j < M; ++j) {
				vet = nAleatorios(vetRegistros, arr[i]);

				begin = std::chrono::steady_clock::now();
				heapSort(vet, matrizComp[i][j], matrizTrocas[i][j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				matrizTempos[i][j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

				/*
				begin = std::chrono::steady_clock::now();
				quickSort(vet, arrComp[i * M + j], arrTrocas[i * M + j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				std::cout << arrComp[i * M + j] << "\t" << arrTrocas[i * M + j] << "\t";
				arrTempos[i * M + j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				std::cout << arrTempos[i * M + j] << std::endl;
				*/

				/*			
				begin = std::chrono::steady_clock::now();
				timSort(vet, arrComp[i * M + j], arrTrocas[i * M + j], Registro::comparaCasos);
				end = std::chrono::steady_clock::now();
				std::cout << arrComp[i * M + j] << "\t" << arrTrocas[i * M + j] << "\t";
				arrTempos[i * M + j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
				std::cout << arrTempos[i * M + j] << std::endl;
				*/
			}

			// Media de comparacoes
			mediasComp[i] = calculaMedia(matrizComp[i], M);
			stdComp[i] = pow(calculaVariancia(matrizComp[i], M, mediasComp[i]), 0.5);
			// Media de trocas
			mediasTrocas[i] = calculaMedia(matrizTrocas[i], M);
			stdTrocas[i] = pow(calculaVariancia(matrizTrocas[i], M, mediasTrocas[i]), 0.5);
			// Media do tempo
			mediasTempos[i] = calculaMedia(matrizTempos[i], M);
			stdTempos[i] = pow(calculaVariancia(matrizTempos[i], M, mediasTempos[i]), 0.5);
		}

		FILE *relatorio;
		relatorio = fopen("saida.txt", "w");
		if(relatorio != NULL)
			escreverTXT(relatorio, arr, matrizComp, matrizTrocas, matrizTempos, mediasComp, 
			mediasTrocas, mediasTempos, stdComp, stdTrocas, stdTempos);
		else
			std::cout << progname << ": falha ao escrever arquivo `saida.txt`\n";
		
		fclose(relatorio);
	}

	return 0;
}

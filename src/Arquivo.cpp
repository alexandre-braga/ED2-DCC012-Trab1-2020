#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>

#include "../include/Registro.hpp"
#include "../include/Arquivo.hpp"

#define M 5 // numero de cojuntos
#define N 5 // numero de registros aleatorios

#define N_ALGORITMOS 4 // numero de algoritmos de ordenacao
#define HEAPSORT  0
#define QUICKSORT 1
#define MERGESORT 2
#define TIMSORT   3

void Arquivo::escreverCSVPorAlgoritmo(std::ofstream& file, int matrizComp[][N][M], int matrizTrocas[][N][M], int matrizTempos[][N][M], 
int i, int n, std::string algoritmo, int codigo)
{
	for(size_t j = 0; j < M; ++j) {
		// escrever N e nome do algoritmo
		file << n << "," << algoritmo << ",";
		// escrever valores
		file << matrizComp[codigo][i][j] << ",";
		file << matrizTrocas[codigo][i][j] << ",";
		file << matrizTempos[codigo][i][j] << "\n";
	}
}

void Arquivo::escreverCSV(std::ofstream& file, int arr[], int matrizComp[][N][M], int matrizTrocas[][N][M], int matrizTempos[][N][M])
{
	file << "N,algoritmo,comparacoes,trocas,tempo_us\n";
	for(size_t i = 0; i < N; ++i) {
		Arquivo::escreverCSVPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, i, arr[i], "HeapSort", HEAPSORT);
		/*
		// escrever outros algoritmos
		Arquivo::escreverCSVPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, i, arr[i], "HeapSort", HEAPSORT);
		Arquivo::escreverCSVPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, i, arr[i], "HeapSort", HEAPSORT);
		Arquivo::escreverCSVPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, i, arr[i], "HeapSort", HEAPSORT);
		*/
	}
}

void Arquivo::escreverTXTPorAlgoritmo(std::ofstream& file, int matrizComp[][N][M], int matrizTrocas[][N][M], 
int matrizTempos[][N][M], int mediasComp[][N], int mediasTrocas[][N], int mediasTempos[][N], 
int stdComp[][N], int stdTrocas[][N], int stdTempos[][N], int i, std::string algoritmo, int codigo)
{
	file << std::setw(11) << algoritmo;
	file << std::setw(15) << "Comparacoes";
	file << std::setw(15) << "Trocas";
	file << std::setw(15) << "Tempo [µs]";
	file << std::endl;
	for(size_t j = 0; j < M; ++j) 
	{
		file << std::setw(11) << j;
		file << std::setw(15) << matrizComp[codigo][i][j];
		file << std::setw(15) << matrizTrocas[codigo][i][j];
		file << std::setw(15) << matrizTempos[codigo][i][j];
		file << std::endl;
	}
	file << std::setw(11) << "Media";
	file << std::setw(15) << mediasComp[codigo][i];
	file << std::setw(15) << mediasTrocas[codigo][i];
	file << std::setw(15) << mediasTempos[codigo][i];
	file << std::endl;
	file << std::setw(11) << "std";
	file << std::setw(15) << stdComp[codigo][i];
	file << std::setw(15) << stdTrocas[codigo][i];
	file << std::setw(15) << stdTempos[codigo][i];
	file << std::endl;
}

void Arquivo::escreverTXT(std::ofstream& file, int arr[], int matrizComp[][N][M], int matrizTrocas[][N][M], 
int matrizTempos[][N][M], int mediasComp[][N], int mediasTrocas[][N], int mediasTempos[][N], 
int stdComp[][N], int stdTrocas[][N], int stdTempos[][N])
{
	for(size_t i = 0; i < N; ++i) 
	{
		file << std::endl << std::setw(11) << "N = " + std::to_string(arr[i]) << std::endl;
		Arquivo::escreverTXTPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, mediasComp, 
			mediasTrocas, mediasTempos, stdComp, stdTrocas, stdTempos, i, "HeapSort", HEAPSORT);
		/*
		// escrever outros algoritmos
		Arquivo::escreverTXTPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, mediasComp, 
			mediasTrocas, mediasTempos, stdComp, stdTrocas, stdTempos, i, "HeapSort", HEAPSORT);
		Arquivo::escreverTXTPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, mediasComp, 
			mediasTrocas, mediasTempos, stdComp, stdTrocas, stdTempos, i, "HeapSort", HEAPSORT);
		Arquivo::escreverTXTPorAlgoritmo(file, matrizComp, matrizTrocas, matrizTempos, mediasComp, 
			mediasTrocas, mediasTempos, stdComp, stdTrocas, stdTempos, i, "HeapSort", HEAPSORT);
		*/
	}
}

void Arquivo::escreverRegistros(std::vector<Registro>& vet, std::ofstream& file)
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

void Arquivo::lerRegistros(std::ifstream& file, std::vector<Registro>& vet) 
{
	// Ignorar header
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Registro r;
	while (file >> r) {
		vet.push_back(r);
	}
}

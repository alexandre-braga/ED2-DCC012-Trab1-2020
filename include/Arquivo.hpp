#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <iostream>
#include <fstream>
#include <vector>

#define M 5 // numero de cojuntos
#define N 5 // numero de registros aleatorios

class Arquivo
{
public:
    static void escreverCSVPorAlgoritmo(std::ofstream& file, int matrizComp[][N][M], int matrizTrocas[][N][M], int matrizTempos[][N][M], 
int i, int n, std::string algoritmo, int codigo);

    static void escreverCSV(std::ofstream& file, int arr[], int matrizComp[][N][M], int matrizTrocas[][N][M], int matrizTempos[][N][M]);
    
    static void escreverTXTPorAlgoritmo(std::ofstream& file, int matrizComp[][N][M], int matrizTrocas[][N][M], 
int matrizTempos[][N][M], int mediasComp[][N], int mediasTrocas[][N], int mediasTempos[][N], 
int stdComp[][N], int stdTrocas[][N], int stdTempos[][N], int i, std::string algoritmo, int codigo);
    
    static void escreverTXT(std::ofstream& file, int arr[], int matrizComp[][N][M], int matrizTrocas[][N][M], 
int matrizTempos[][N][M], int mediasComp[][N], int mediasTrocas[][N], int mediasTempos[][N], 
int stdComp[][N], int stdTrocas[][N], int stdTempos[][N]);

    static void escreverRegistros(std::vector<Registro>& vet, std::ofstream& file);

    static void lerRegistros(std::ifstream& file, std::vector<Registro>& vet);
};

#endif /* ARQUIVO_HPP */
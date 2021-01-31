#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

#include "./include/Registro.hpp"
#include "./include/Arquivo.hpp"
#include "./include/sortalgos.hpp"

#define ERR_NENHUM_ARG 1
#define ERR_FALHA_ARQ  2
#define M 5 // numero de cojuntos
#define N 5 // numero de registros aleatorios

#define N_ALGORITMOS 4 // numero de algoritmos de ordenacao
#define HEAPSORT  0
#define QUICKSORT 1
#define MERGESORT 2
#define TIMSORT   3

void exibirRegistros(std::vector<Registro>& vet, size_t n)
{
    std::cout << std::setw(16) << std::left << "Data";
    std::cout << std::setw(16) << std::left << "Estado";
    std::cout << std::setw(16) << std::left << "Nome";
    std::cout << std::setw(16) << std::left << "Codigo";
    std::cout << std::setw(16) << std::left << "Casos diarios";
    std::cout << std::setw(16) << std::left << "Mortes diarias";
    std::cout << std::endl;
    for(size_t i = 0; i < n && i < vet.size(); ++i) {
        Registro& r = vet[i];
        std::cout << std::setw(16) << std::left << r.date();
        std::cout << std::setw(16) << std::left << r.state();
        std::cout << std::setw(16) << std::left << r.city();
        std::cout << std::setw(16) << std::left << r.code();
        std::cout << std::setw(16) << std::left << r.cases();
        std::cout << std::setw(16) << std::left << r.deaths();
        std::cout << std::endl;
    }
}

int main()
{
	std::ifstream fin;
    fin.open("brazil_covid19_cities_processado.csv");

    if (!fin.is_open()) 
    {
        std::cerr << "Falha ao abrir o arquivo `brazil_covid19_cities_processado.csv`\n";
        exit(ERR_FALHA_ARQ);
    }

    std::vector<Registro> vetRegistros;
    Arquivo::lerRegistros(fin, vetRegistros);
    fin.close();

    // Exibir registros pré-processados
    std::cout << "Registros pré-processados: \n\n";
    exibirRegistros(vetRegistros, 10);

    int op;
    std::cout << "\nOrdenação de registros aleatórios: \n";
    std::cout << "Imprimir em console (0) ou salvar em arquivo (1)\n";
    std::cout << "Digite a opção: ";
    std::cin >> op;
    
    int comparacoes = 0;
    int trocas = 0;

    std::vector<Registro> vetControle;
    if(op) {
        std::ofstream file;
        vetControle = Registro::nAleatorios(vetRegistros, 100);

        std::vector<Registro> vet = vetControle;
        heapSort(vet, comparacoes, trocas, Registro::comparaCasos);
        file.open("heapSort.csv");
        if(!file.fail()) {
            Arquivo::escreverRegistros(vet, file);
            std::cout << "Registros salvos em `heapSort.csv`\n";
        }
        else
            std::cout << "Falha ao escrever arquivo `heapSort.csv`\n";
		file.close();
        
        vet = vetControle;
        quickSort(vet, 0, vet.size()-1, comparacoes, trocas, Registro::comparaCasos);
        file.open("quickSort.csv");
        if(!file.fail()) {
            Arquivo::escreverRegistros(vet, file);
            std::cout << "Registros salvos em `quickSort.csv`\n";
        }
        else
            std::cout << "Falha ao escrever arquivo `quickSort.csv`\n";
		file.close();
        
    }
    else {
        vetControle = Registro::nAleatorios(vetRegistros, 10);

        std::vector<Registro> vet = vetControle;
        heapSort(vet, comparacoes, trocas, Registro::comparaCasos);
        std::cout << std::endl << std::setw(48) << std::right << "HEAPSORT" << std::endl;
        exibirRegistros(vet, vet.size());
        
        vet = vetControle;
        quickSort(vet, 0, vet.size()-1, comparacoes, trocas, Registro::comparaCasos);
        std::cout << std::endl << std::setw(48) << std::right << "QUICKSORT" << std::endl;
        exibirRegistros(vet, vet.size());
    }
		
	return 0;
}
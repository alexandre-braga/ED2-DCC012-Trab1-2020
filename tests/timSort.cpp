#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#include "../include/timSort.hpp"
#include "../include/Registro.hpp"

#define MAX_REGISTROS 1000

using namespace std;

/*Compara Cases*/
int compByCases(const Registro& r1, const Registro& r2)
{
    if(r1.cases() < r2.cases()) 
        return -1;
    else if(r2.cases() < r1.cases())
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    const char* nomePrograma = *argv; 

    if(argc != 2){
        cerr << "Uso: " << nomePrograma << " ARQUIVOCSV\n";
        return 1;
    }

    ifstream arquivoDeEntrada(*++argv);

    if(!arquivoDeEntrada.is_open()){
        cerr << nomePrograma << ": Falha ao abrir arquivo\n";
        return 2;
    }

    int count = 0;
    std::vector<Registro> vet;
    arquivoDeEntrada.ignore(numeric_limits<streamsize>::max(),'\n');
    Registro r;

    while(arquivoDeEntrada >> r && ++count < MAX_REGISTROS){
        vet.push_back(std::move(r));
    }

    timSort(vet.begin(), vet.end(), compByCases);

    for(auto& registro : vet){
        cout << registro << '\n';
    }
	return 0;
}
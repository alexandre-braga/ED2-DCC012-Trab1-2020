#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <cassert>

#include "../include/Registro.hpp"
using namespace std;
using RegIterator = vector<Registro>::iterator; 

const int MIN_RUN = 32;
const int MAX_RUN = 64;


/*Compara Cases*/
int comp(const Registro& r1, const Registro& r2)
{
    if(r1.cases() < r2.cases()) 
        return -1;
    else if(r2.cases() < r1.cases())
        return 1;
    return 0;
}

/*Insertion Sort: */
void insertionSort(RegIterator inicio, RegIterator fim, int(*comp)(const Registro&, const Registro&))    
{ 
    for(RegIterator i = inicio + 1; i < fim; i++){
        for(RegIterator j = i; j > inicio && comp(*j, *(j-1)) < 0; j--){
            std::swap(*j, *(j-1));
        }
    }
} 


/*Calcula tamanho das Runs: */
int calculaFimRun(RegIterator inicio, RegIterator limiteSuperior){
    RegIterator fimrun = inicio;
    RegIterator a = inicio;
    size_t totalDeElementos = limiteSuperior - inicio;
    if(totalDeElementos <= 1){
        return inicio;
    }
    if((a + 1)->cases() >= a->cases()){
        while((a + 1)->cases() >= a->cases()){
            a++;
            /*se o tamanho atual n é maior q o max da run 64*/
            if( a - inicio >= MAX_RUN || a >= limiteSuperior  )
                return fimrun;
            fimrun++;
        }
    }
    else{
        while((a + 1)->cases() <= a->cases()){
            a++;
            /*se o tamanho atual n é maior q o max da run 64*/
            if( a - inicio >= MAX_RUN || a >= limiteSuperior  )
                return fimrun;
            fimrun++;
        }
        reverse(a, fimrun + 1);
    }
    /*se o tamanho atual n é menor q o min da run 32*/
    if(fimrun - a < MIN_RUN) 
        fimrun = inicio + MIN_RUN;
    return fimrun;
}


/*Merge Sort:*/

/*Algumas otimizações são feitas no MergeSort utilizado no TimSort visando diminuir o custo do algoritmo, mais precisamente o espaço de memória adicional e o número de comparações. Em algumas implementações, geralmente cria-se um vetor temporário cujo tamanho é dado pela soma dos dois sub-vetores de entrada. Porém isso não é necessário quando deseja-se fazer o merge de dois sub-vetores cujos elementos são consecutivos, pois criar um vetor temporário com o tamanho do menor sub-vetor é suficiente. O processo de merge pode ser feito da seguinte forma: Um vetor temporário é criado com o tamanho do menor dos dois Runs que são combinados.
Copia-se o Run mais curto para o vetor temporário.
Marca-se a posição corrente com os primeiros elementos do maior Run e do "Run" temporário.
Em cada passo seguinte compare os primeiros elementos do maior Run e do Run temporário e mova o menor para o vetor ordenado. Move-se (incrementa) o endereço base do Run que teve o elemento movido.
Repete o passo 4 até um dos Runs esvaziar.
Adiciona todos os elementos do Run remanescente para o final do Run ordenado.
-wikipedia*/


/*Merge do Caio*/
vector<Registro> merge(vector<Registro>& vet1, vector<Registro>& vet2, int(*comp)(const Registro&, const Registro&)) {
    if (vet1.empty())
        return vet2;
    if (vet2.empty())
        return vet1;

    vector<Registro> merged;
    vector<Registro>::iterator vetit1 = vet1.begin();
    vector<Registro>::iterator vetit2 = vet2.begin();

    while (vetit1 != vet1.end() && vetit2 != vet2.end()) {
        if (comp(*vetit1, *vetit2) <= 0) {
            merged.push_back(*vetit1++);
        } else {
            merged.push_back(*vetit2++);
        }
    }
    while (vetit1 != vet1.end()) {
        merged.push_back(*vetit1++);
    }
    while (vetit2 != vet2.end()) {
        merged.push_back(*vetit2++);
    }
    return merged;
}

/*Isto é feito da seguinte maneira:
Cria-se uma pair stack <Posição do primeiro elemento do Run>-<Tamanho do Run>.
Insere-se o Run atual à pair stack.
Avalia se deve ser feito o merge.
Avaliação: Sejam X, Y e Z os 3 primeiros Runs da pair stack; X > Y + Z e Y > Z. Se uma das duas condições não é satisfeita, então é feito o merge do Run Y com o Run de menor tamanho entre X e Z.
Para qualquer Run que não tenha sido considerado, basta tomá-lo e ir para o passo 2 até que reste apenas um Run na pilha (que é o vetor final já ordenado).
-wikipedia
*/


/*Faz o merge das Runs em ordem crescente, e mantém a estabilidade */

/*
z > x + y 
y > x

x
yy
zzzz
*/

void ajustaPilhaDeRuns (vector<vector<Registro>>& pilhaDeRuns, vector<Registro>& vet, int(*comp)(const Registro&, const Registro&)){
     size_t fim = 0;

    while (pilhaDeRuns.size() >= 2) {
        for (size_t i = 1; i + 1 <= pilhaDeRuns.size(); i++) {
            std::vector<Registro>& menor = pilhaDeRuns[i-1];
            std::vector<Registro>& medio = pilhaDeRuns[i];
            std::vector<Registro>& maior = pilhaDeRuns[i+1];
            if (maior.size() >= menor.size() + medio.size()) {
                /*if (menor.size() > medio.size())*/
                   medio = merge(pilhaDeRuns[i-1], pilhaDeRuns[i], comp);
            }
            else if (menor.size() > maior.size())
                medio = merge(pilhaDeRuns[i], pilhaDeRuns[i+1], comp);
            else if (menor.size() < maior.size())
                medio = merge(pilhaDeRuns[i], pilhaDeRuns[i-1], comp);
            fim = i;
        }
    }
    std::swap(vet,pilhaDeRuns[fim]);
}

void timSort(RegIterator begin, RegIterator end, int(*comp)(const Registro&, const Registro&)){
    vector<vector<Registro>> pilhaDeRuns;
    for (RegIterator lo = begin, ho ; lo != end; i = ho){ 
        ho = calculaFimRun(lo, end);
        insertionSort(lo, ho, comp); 
        pilhaDeRuns.push_back({lo,ho});
    }
    ajustaPilhaDeRuns(pilhaDeRuns,vet, comp);
}

int main(int argc, char *argv[]){

    std::vector<Registro> vetRegistros;
	Registro r;
	ifstream f;
	ofstream arquivoSaida;

	if (argc < 2) {
		std::cerr << "Nenhum arquivo fornecido\n";
		exit(1);
	}

	arquivoSaida.open("brazil_covid19_cities_timSorted.csv");
	if (!arquivoSaida.is_open()) {
		std::cerr << "Falha ao abrir o arquivo de saída\n";
		exit(2);
	}
	f.open(*++argv);


	if (f.is_open()) {
		f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int i = 0;
		while (f >> r && i++ < 32) {
			vetRegistros.push_back(r);
		}

		insertionSort(vetRegistros.begin(), vetRegistros.end(), comp);

		for (const Registro& r : vetRegistros) {
			arquivoSaida << r << '\n';
		}
		
	} else {
		std::cerr << "Erro ao abrir o arquivo `" << *argv << "\n";
		return 2;
	}
	
	return 0;

}
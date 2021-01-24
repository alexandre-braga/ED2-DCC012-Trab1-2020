#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

#include "../include/Registro.hpp"
using namespace std;

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
/*j-- pra um j = 0*/
void insertionSort(vector<Registro>& vet, size_t inicio, size_t fim, int(*comp)(const Registro&, const Registro&))    
{ 
    for (size_t i = inicio + 1; i <= fim; i++) 
    { 
        Registro pivo = vet[i]; 
        size_t j = i - 1; 
        while (j > inicio && comp(vet[j],pivo)){ 
            vet[j+1] = vet[j]; 
            j--; 
        } 
        vet[j+1] = pivo; 
    } 
} 

/*Começando a partir da posição do elemento atual, procure o Run (um sub-vetor ordenado) no vetor de entrada. Por definição o Run será pelo menos o elemento atual e o próximo (pois formará um vetor ordenado, seja crescente ou decrescente), sendo que a composição de mais elementos no Run dependerá da forma como os elementos estão organizados. O próximo elemento é considerado se ao considerá-lo no Run atual, o Run continue ordenado. Se o Run final está ordenado de forma decrescente, os elementos são "reordenados" em uma ordem crescente (por meio de um algoritmo  simples de inversão de vetor).
-wikipedia
*/

int verificaFimRun(vector<Registro>& vet, size_t i){
    int fimrun = i;
    int a = i;
    if(vet[i+1].cases()>=vet[i].cases()){
        while(vet[i].cases()<=vet[i+1].cases()){
            i++;
            if( i >= a + MAX_RUN || i >= vet.size())
                return fimrun;
            fimrun++;
        }
    }
    else{
        while(vet[i].cases()>=vet[i+1].cases()){
           i++;
           if( i >= a + MAX_RUN || i >= vet.size() )
                return fimrun;
           fimrun++;
        }
        reverse(vet.begin() + i, vet.begin() + fimrun + 1);
    }
    if(fimrun < a + MIN_RUN)
        fimrun += (int)fabs(fimrun - a - MIN_RUN);
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
            if (maior.size() > menor.size() + medio.size()) {
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

void timSort(vector<Registro>& vet, int(*comp)(const Registro&, const Registro&)){
    vector<vector<Registro>> pilhaDeRuns;
    for (size_t i = 0, j = 0; i < vet.size(); i+=j){ 
        j = verificaFimRun(vet,i); 
        insertionSort(vet, i, j, comp); 
        std::vector<Registro> coord(vet.begin() + i, vet.begin() + j + 1);
        i = 156
        j = 156
        i = 312
        j = 312
        pilhaDeRuns.push_back(coord);
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

		while (f >> r) {
			vetRegistros.push_back(r);
		}

		timSort(vetRegistros, comp);

		for (const Registro& r : vetRegistros) {
			arquivoSaida << r << '\n';
		}
		
	} else {
		std::cerr << "Erro ao abrir o arquivo `" << *argv << "\n";
		return 2;
	}
		
	return 0;

}
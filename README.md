# Trabalho de Estrutura De Dados II
Repositório para armazenar e organizar os arquivos para o trabalho de ED2 do período 2020/3 (UFJF).

Integrantes:
- Alexandre Vitor Silva Braga
- Caio Cedrola Rocha
- Marcelo Ian Rezende Menezes
- Igor Correa Rodrigues

## Descrição
Vista a importância da ordenação de dados para a organização de sistemas, este trabalho avalia o desempenho de 3 algoritmos de ordenação (HeapSort, QuickSort e TimSort) para os dados de monitoramento da COVID-19 no Brasil, divulgados pelo Ministério da Saúde na [Plataforma Coronavírus Brasil](https://covid.saude.gov.br/). 

## Instruções para compilação e execução
### Main
```
make
./main brazil_covid19_cities.csv
```
A main.cpp implementa o pré-processamento dos dados e realiza a ordenação de N registros aleatórios para cada algoritmo, escrevendo os resultados nos arquivos `saida.txt` e `saida.csv`.
### Módulo de testes
```
make teste
./teste
```
O arquivo teste.cpp permite a verificação do funcionamento dos algoritmos de ordenação, seja pela impressão dos dados no terminal ou pela impressão nos arquivos `heapSort.csv`, `quickSort.csv` e `timSort.csv`.
## Gráficos
Os gráficos podem ser encontrados na pasta `python`.

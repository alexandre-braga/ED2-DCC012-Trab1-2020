CC=g++

CC_FLAGS=-W -Wall -pedantic -std=c++11

teste: ./src/Registro.cpp ./tests/pre_processamento.cpp
	$(CC) $(CC_FLAGS) -o $@ $^

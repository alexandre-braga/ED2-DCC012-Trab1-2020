CC=g++

CC_FLAGS=-W -Wall -pedantic -std=c++11

main: ./src/Registro.cpp ./src/HeapSort.cpp ./main.cpp
	$(CC) $(CC_FLAGS) -o $@ $^

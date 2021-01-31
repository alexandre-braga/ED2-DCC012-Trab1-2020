CC=g++

CC_FLAGS=-W -Wall -pedantic -std=c++17

build: main

main: ./src/*.cpp main.cpp
	$(CC) $(CC_FLAGS) -o $@ $^

teste: ./src/*.cpp teste.cpp
	$(CC) $(CC_FLAGS) -o $@ $^

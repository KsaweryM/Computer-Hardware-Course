app: main.o util.o
	g++ main.o util.o -o app

main.o: main.cpp util.h
	g++ -std=c++20 -Wall -c main.cpp -o main.o

util.o: util.cpp util.h
	g++ -std=c++20 -Wall -c util.cpp -o util.o

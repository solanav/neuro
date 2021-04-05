CC=g++

CPPFLAGS=-g -std=c++17 -Iinclude/
LDFLAGS=-g
SRC=./src/
INCLUDE=./include/

compilar: all

all: mc_perceptron

clean:
	rm -f *.o

mc_perceptron: mc_perceptron.o red_neuronal.o lector.o mates.o
	$(CC) $(LDFLAGS) -o mc_perceptron mc_perceptron.o red_neuronal.o lector.o mates.o $(LDLIBS)

mc_perceptron.o: $(SRC)mc_perceptron.cpp $(INCLUDE)red_neuronal.h $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -c $(SRC)mc_perceptron.cpp

red_neuronal.o: $(SRC)red_neuronal.cpp $(INCLUDE)red_neuronal.h
	$(CC) $(CPPFLAGS) -c $(SRC)red_neuronal.cpp

lector.o: $(SRC)lector.cpp $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -c $(SRC)lector.cpp

mates.o: $(SRC)mates.cpp $(INCLUDE)mates.h
	$(CC) $(CPPFLAGS) -c $(SRC)mates.cpp
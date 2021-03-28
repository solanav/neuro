CC=g++

CPPFLAGS=-g -std=c++17 -Iinclude/
LDFLAGS=-g
SRC=./src/
INCLUDE=./include/

compilar: all

all: mc_perceptron

clean:
	rm -f *.o

mc_perceptron: mc_perceptron.o neurona.o conexion.o capa.o red_neuronal.o lector.o
	$(CC) $(LDFLAGS) -o mc_perceptron mc_perceptron.o neurona.o conexion.o capa.o red_neuronal.o lector.o $(LDLIBS)

mc_perceptron.o: $(SRC)mc_perceptron.cpp $(INCLUDE)red_neuronal.h $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -c $(SRC)mc_perceptron.cpp

neurona.o: $(SRC)neurona.cpp $(INCLUDE)neurona.h $(INCLUDE)conexion.h
	$(CC) $(CPPFLAGS) -c $(SRC)neurona.cpp

conexion.o: $(SRC)conexion.cpp $(INCLUDE)conexion.h $(INCLUDE)neurona.h
	$(CC) $(CPPFLAGS) -c $(SRC)conexion.cpp

capa.o: $(SRC)capa.cpp $(INCLUDE)capa.h $(INCLUDE)neurona.h
	$(CC) $(CPPFLAGS) -c $(SRC)capa.cpp

red_neuronal.o: $(SRC)red_neuronal.cpp $(INCLUDE)red_neuronal.h $(INCLUDE)capa.h
	$(CC) $(CPPFLAGS) -c $(SRC)red_neuronal.cpp

lector.o: $(SRC)lector.cpp $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -c $(SRC)lector.cpp
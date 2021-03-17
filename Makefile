CC=g++

CPPFLAGS=-g -Iinclude/
LDFLAGS=-g
SRC=./src/
INCLUDE=./include/

all: clean mp perceptron adaline clean

ayuda_mp:
	echo "no, aprendes tu solito"

compila_mp: clean mp

ejecuta_mp:
	./mp

clean:
	rm -f *.o mp

adaline: adaline.o neurona.o conexion.o capa.o red_neuronal.o lector.o
	$(CC) $(LDFLAGS) -o adaline adaline.o neurona.o conexion.o capa.o red_neuronal.o lector.o $(LDLIBS)

perceptron: perceptron.o neurona.o conexion.o capa.o red_neuronal.o lector.o
	$(CC) $(LDFLAGS) -o perceptron perceptron.o neurona.o conexion.o capa.o red_neuronal.o lector.o $(LDLIBS)

mp: mp.o neurona.o conexion.o capa.o red_neuronal.o
	$(CC) $(LDFLAGS) -o mp mp.o neurona.o conexion.o capa.o red_neuronal.o $(LDLIBS)

adaline.o: $(SRC)adaline.cpp $(INCLUDE)neurona.h $(INCLUDE)conexion.h $(INCLUDE)red_neuronal.h $(INCLUDE)capa.h
	$(CC) $(CPPFLAGS) -c $(SRC)adaline.cpp

perceptron.o: $(SRC)perceptron.cpp $(INCLUDE)neurona.h $(INCLUDE)conexion.h $(INCLUDE)red_neuronal.h $(INCLUDE)capa.h
	$(CC) $(CPPFLAGS) -c $(SRC)perceptron.cpp

mp.o: $(SRC)mp.cpp $(INCLUDE)neurona.h $(INCLUDE)conexion.h $(INCLUDE)red_neuronal.h $(INCLUDE)capa.h
	$(CC) $(CPPFLAGS) -c $(SRC)mp.cpp

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
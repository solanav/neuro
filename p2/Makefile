CC=g++

CPPFLAGS=-g -std=c++17 -Iinclude/
LDFLAGS=-g
SRC=./src/
INCLUDE=./include/

compilar: all

clean:
	rm -f *.o 

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
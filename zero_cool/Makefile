CC=g++

CPPFLAGS=-g -std=c++17 -Iinclude/
LDFLAGS=-g -pthread
SRC=./src/
INCLUDE=./include/
OBJ=./obj/
PROF=./prof/
FILENAME:=$(shell date +%Y-%m-%d_%H-%M-%S)

compilar: all

all: create_obj main

profiler:
	mkdir -p $(PROF)
	valgrind --tool=callgrind --callgrind-out-file=$(PROF)$(FILENAME) ./main
	gprof2dot --format=callgrind --output=$(PROF)$(FILENAME).dot $(PROF)$(FILENAME)
	dot -Tpng $(PROF)$(FILENAME).dot -o $(PROF)$(FILENAME).png
	feh $(PROF)$(FILENAME).png

create_obj:
	mkdir -p $(OBJ)

clean:
	rm -f main $(OBJ)

main: $(OBJ)main.o $(OBJ)red_neuronal.o $(OBJ)lector.o $(OBJ)mates.o
	$(CC) $(LDFLAGS) -o main $(OBJ)main.o $(OBJ)red_neuronal.o $(OBJ)lector.o $(OBJ)mates.o $(LDLIBS)

$(OBJ)main.o: $(SRC)main.cpp $(INCLUDE)red_neuronal.h $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -o $(OBJ)main.o -c $(SRC)main.cpp

$(OBJ)red_neuronal.o: $(SRC)red_neuronal.cpp $(INCLUDE)red_neuronal.h
	$(CC) $(CPPFLAGS) -o $(OBJ)red_neuronal.o -c -c $(SRC)red_neuronal.cpp

$(OBJ)lector.o: $(SRC)lector.cpp $(INCLUDE)lector.h
	$(CC) $(CPPFLAGS) -o $(OBJ)lector.o -c -c $(SRC)lector.cpp

$(OBJ)mates.o: $(SRC)mates.cpp $(INCLUDE)mates.h
	$(CC) $(CPPFLAGS) -o $(OBJ)mates.o -c -c $(SRC)mates.cpp
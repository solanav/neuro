#include <iostream>
#include <fstream>
#include <string>

#include "lector.h"

Lector::Lector()
{
    entradas_entrenamiento = std::vector<std::vector<float>>();
    salidas_entrenamiento = std::vector<std::vector<float>>();
    entradas_test = std::vector<std::vector<float>>();
    salidas_test = std::vector<std::vector<float>>();
}

Lector::~Lector() {}

void Lector::leer(char *fichero)
{
    std::string line;
    char c;
    std::ifstream infile(fichero);
    infile >> num_entradas >> num_salidas;

    while (getline(infile, line))
    {
        std::cout << line << std::endl;
    }

    infile.close();
    
}

void Lector::leer1(char *fichero, float por)
{
    leer(fichero);
}
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include "lector.h"

Lector::Lector()
{
    entradas_entrenamiento = std::vector<std::vector<float>>();
    salidas_entrenamiento = std::vector<std::vector<float>>();
    entradas_test = std::vector<std::vector<float>>();
    salidas_test = std::vector<std::vector<float>>();
    data = std::vector<std::string>();
}

Lector::~Lector() {}

void Lector::leer(char *fichero)
{
    std::string line;
    char c, *arr;
    std::ifstream infile(fichero);
    infile >> num_entradas >> num_salidas;

    /* Esto es para ignorar el resto de la primera linea */
    infile.ignore(std::numeric_limits<std::streamsize>::max() ,'\n');


    while (getline(infile, line))
    {
        data.push_back(line);
    }

    infile.close();
    
}

void Lector::leer1(char *fichero, float por)
{
    leer(fichero);

    int num_entreno=data.size() * por;
    std::string s_aux;
    float f_aux;
    std::vector<float> v_aux = std::vector<float>();

    std::random_shuffle ( data.begin(), data.end() );

    for (int i = 0; i < num_entreno; i++)
    {
        s_aux = data.back();
        std::cout << s_aux << std::endl;
        data.pop_back();
        for(int j = 0; j < num_entradas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }

        entradas_entrenamiento.push_back(v_aux);
        v_aux.clear();
        for(int j = 0; j < num_salidas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        salidas_entrenamiento.push_back(v_aux);
        v_aux.clear();
    }
    for (int i = 0; i < data.size(); i++)
    {
        s_aux = data.back();
        data.pop_back();
        for(int j = 0; j < num_entradas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        entradas_test.push_back(v_aux);
        v_aux.clear();
        for(int j = 0; j < num_salidas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        salidas_test.push_back(v_aux);
        v_aux.clear();
    }
    
}

void Lector::leer2(char * fichero){
    leer(fichero);

    std::string s_aux;
    float f_aux;
    std::vector<float> v_aux = std::vector<float>();

    for (int i = 0; i < data.size(); i++)
    {
        s_aux = data.back();
        data.pop_back();
        for(int j = 0; j < num_entradas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        entradas_entrenamiento.push_back(v_aux);
        entradas_test.push_back(v_aux);
        v_aux.clear();
        for(int j = 0; j < num_salidas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        salidas_entrenamiento.push_back(v_aux);
        salidas_test.push_back(v_aux);
        v_aux.clear();
    }
}

void Lector::leer3(char *fichero_entreno, char *fichero_test){
    leer(fichero_entreno);

    std::string s_aux;
    float f_aux;
    std::vector<float> v_aux = std::vector<float>();

    for (int i = 0; i < data.size(); i++)
    {
        s_aux = data.back();
        data.pop_back();
        for(int j = 0; j < num_entradas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        entradas_entrenamiento.push_back(v_aux);
        v_aux.clear();
        for(int j = 0; j < num_salidas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        salidas_entrenamiento.push_back(v_aux);
        v_aux.clear();
    }
    data.clear();
    leer(fichero_test);
    for (int i = 0; i < data.size(); i++)
    {
        s_aux = data.back();
        data.pop_back();
        for(int j = 0; j < num_entradas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        entradas_test.push_back(v_aux);
        v_aux.clear();
        for(int j = 0; j < num_salidas; j++){
            f_aux = std::stof(s_aux.substr(0, s_aux.find(' ')));
            v_aux.push_back(f_aux);
        }
        salidas_test.push_back(v_aux);
        v_aux.clear();
    }
}
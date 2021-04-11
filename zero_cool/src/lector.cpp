#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <iterator>

#include "lector.h"
#include "mates.h"

Lector::Lector()
{
    entradas_entrenamiento = std::vector<std::vector<float>>();
    salidas_entrenamiento = std::vector<std::vector<float>>();
    entradas_test = std::vector<std::vector<float>>();
    salidas_test = std::vector<std::vector<float>>();
    data = std::vector<std::string>();
}

Lector::~Lector() {}

std::vector<std::string> split(std::string s)
{
    // Magic: DO NOT TOUCH
    std::istringstream buf(s);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> tokens(beg, end);

    return tokens;
}

// This takes a vector and puts the
std::vector<float> dataToFloat(std::vector<std::string> s, int start, int finish)
{
    std::vector<float> res = std::vector<float>();
    for(int i = start; i < finish; i++){
        res.push_back(std::stof(s[i]));
    }

    return res;
}

std::vector<float> tensor_max(std::vector<std::vector<float>> tensor1, std::vector<std::vector<float>> tensor2)
{
    std::vector<float> max(tensor1[0].size(), -1);

    for (int i = 0; i < tensor1.size(); i++)
        for (int j = 0; j < tensor1[i].size(); j++)
            if (tensor1[i][j] > max[j])
                max[j] = tensor1[i][j];

    for (int i = 0; i < tensor2.size(); i++)
        for (int j = 0; j < tensor2[i].size(); j++)
            if (tensor2[i][j] > max[j])
                max[j] = tensor2[i][j];

    return max;
}

void Lector::normalize()
{
    std::vector<float> max = tensor_max(entradas_entrenamiento, entradas_test);

    for (int i = 0; i < entradas_entrenamiento.size(); i++)
        for (int j = 0; j <  entradas_entrenamiento[0].size(); j++)
            entradas_entrenamiento[i][j] = ((entradas_entrenamiento[i][j] / max[j]) * 2.0) - 1.0;

    for (int i = 0; i < entradas_test.size(); i++)
        for (int j = 0; j <  entradas_test[0].size(); j++)
            entradas_test[i][j] = ((entradas_test[i][j] / max[j]) * 2.0) - 1.0;
}

void Lector::leer(const char *fichero)
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

void Lector::leer1(const char *fichero, float por)
{
    leer(fichero);

    int num_entreno = data.size() * por;

    std::string s_aux;
    std::vector<float> v_aux = std::vector<float>();
    std::vector<std::string> stuff;

    std::random_shuffle (data.begin(), data.end());

    for (int i = 0; i < num_entreno; i++)
    {
        s_aux = data.back();
        stuff = split(s_aux);
        data.pop_back();

        // Sacamos las entradas
        entradas_entrenamiento.push_back(dataToFloat(stuff, 0, num_entradas));

        // Sacamos las salidas
        salidas_entrenamiento.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
    }

    int entrena_size = data.size();
    for (int i = 0; i < entrena_size; i++)
    {
        s_aux = data.back();
        stuff = split(s_aux);
        data.pop_back();

        // Sacamos las entradas
        entradas_test.push_back(dataToFloat(stuff, 0, num_entradas));

        // Sacamos las salidas
        salidas_test.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
    }
}

void Lector::leer2(const char * fichero){
    leer(fichero);

    std::string s_aux;
    std::vector<std::string> stuff;

    int entrena_size = data.size();
    for (int i = 0; i < entrena_size; i++)
    {
        s_aux = data.back();
        stuff = split(s_aux);
        data.pop_back();

        entradas_entrenamiento.push_back(dataToFloat(stuff, 0, num_entradas));
        entradas_test.push_back(dataToFloat(stuff, 0, num_entradas));

        salidas_entrenamiento.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
        salidas_test.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
    }
}

void Lector::leer3(const char *fichero_entreno, const char *fichero_test){
    leer(fichero_entreno);

    std::string s_aux;
    std::vector<std::string> stuff;

    int entrena_size = data.size();
    for (int i = 0; i < entrena_size; i++)
    {
        s_aux = data.back();
        stuff = split(s_aux);
        data.pop_back();

        // Sacamos las entradas
        entradas_entrenamiento.push_back(dataToFloat(stuff, 0, num_entradas));

        // Sacamos las salidas
        salidas_entrenamiento.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
    }
    data.clear();
    leer(fichero_test);

    int entrena_size2 = data.size();
    for (int i = 0; i < entrena_size2; i++)
    {
        s_aux = data.back();
        stuff = split(s_aux);
        data.pop_back();

        // Sacamos las entradas
        entradas_test.push_back(dataToFloat(stuff, 0, num_entradas));

        // Sacamos las salidas
        salidas_test.push_back(dataToFloat(stuff, num_entradas, num_salidas+num_entradas));
    }
}
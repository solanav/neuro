#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <thread>

#include "red_neuronal.h"
#include "lector.h"
#include "mates.h"

#define MAX_EPOCAS 500000

void test_and()
{
    Lector l = Lector();
    l.leer2((char *)"data/and.txt");

    RedNeuronal red(2, 0.01, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_xor()
{
    Lector l = Lector();
    l.leer2((char *)"data/xor.txt");

    RedNeuronal red(4, 0.02, BINARIA, l, "/dev/null", 500000);
    red.train();
    red.test();
}

void test_or()
{
    Lector l = Lector();
    l.leer2((char *)"data/or.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_nand()
{
    Lector l = Lector();
    l.leer2((char *)"data/nand.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_problema_real1()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real1.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 1000);
    red.train2();
    red.test();
    std::cout << "problema_real1" << std::endl;
}

void test_problema_real2()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real2.txt");

    RedNeuronal red(4, 0.4, BIPOLAR, l, "/dev/null", 1000);
    red.train2();
    red.test();
    std::cout << "problema_real2" << std::endl;
}

void test_problema_real3()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real3.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real3" << std::endl;
}

void test_problema_real4()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real4.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real4" << std::endl;
}

void test_problema_real5()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real5.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real5" << std::endl;
}

void test_problema_real6()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real6.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real6" << std::endl;
}

int main(int argc, char const *argv[])
{
    if(argc < 8)
    {
        std::cout
            << "Uso: ./main" << "\n"
            << "\t" << "1. (fichero datos) [String]" << "\n"
            << "\t" << "2. (modo de lectura) [1, 2, 3]" << "\n"
            << "\t" << "3. (tamaño capa oculta) [1 - MAX_INT]" << "\n"
            << "\t" << "4. (tasa de aprendizaje) [0.0 - 1.0]" << "\n"
            << "\t" << "5. (bipolar[0] o binaria[1]) [0, 1]" << "\n"
            << "\t" << "6. (algoritmo selecionado) [0, 1]" << "\n"
            << "\t" << "7. (máximas iteraciones) [1 - MAX_INT]" << "\n"
            << "\t" << "8. (no normalizar[0] o normalizar[1]) [0, 1]" << "\n"
            << "\t" << "9. (porcentaje o fichero de test, según modo) [0 - 100]" << "\n\n"
            << "Ejemplos:" << "\n"
            << "\t" << "./main data/problema_real1.txt 1 4 0.2 0 0 1000 50" << "\n"
            << "\t" << "./main data/problema_real1.txt 2 4 0.2 0 0 1000" << "\n"
            << "\t" << "./main data/problema_real2.txt 3 4 0.2 0 0 1000 data/problema_real2_no_etiquetados.txt" << "\n"
            << std::endl;

        return -1;
    }
    auto fichero_datos = argv[1];
    auto modo_lectura = std::stoi(argv[2]);
    auto capa_oculta = std::stoi(argv[3]);
    auto tasa_aprendizaje = std::stof(argv[4]);
    auto bi = std::stof(argv[5]);
    auto algoritmo = std::stoi(argv[6]);
    auto max_iter = std::stof(argv[7]);
    auto normalizar = std::stoi(argv[8]);

    std::cout << fichero_datos << std::endl;

    std::ifstream f(fichero_datos);
    if(!f.good()){
        std::cout << "Archivo no existe" << std::endl;
        return -1;
    }

    Lector l;
    if(modo_lectura == 1)
        l.leer1(fichero_datos, std::stof(argv[9]) / 100.0);
    else if(modo_lectura == 2)
        l.leer2(fichero_datos);
    else if(modo_lectura == 3)
        l.leer3(fichero_datos, argv[9]);
    else
        std::cout << "Modo inválido" << std::endl;

    if (normalizar == 1)
        l.normalize();

    std::cout
        << "Ejecutando con estas opciones:" << "\n"
        << "\t" << "- Fichero datos: " << argv[1] << "\n"
        << "\t" << "- Modo de lectura: " << argv[2] << "\n"
        << "\t" << "- Tamaño capa oculta: " << argv[3] << "\n"
        << "\t" << "- Tasa de aprendizaje: " << argv[4] << "\n"
        << "\t" << "- Bipolar[0] o binaria[1]: " << argv[5] << "\n"
        << "\t" << "- Algoritmo selecionado: " << argv[6] << "\n"
        << "\t" << "- Maximas iteraciones: " << argv[7] << "\n\n"
        << std::endl;

    // Creamos la red con los parametros dados y empezamos
    RedNeuronal red(capa_oculta, tasa_aprendizaje, bi, l, "/dev/null", max_iter);
    if (algoritmo == 0)
        red.train();
    else if (algoritmo == 1)
        red.train2();
    else
        std::cout << "Algoritmo invalido [0 o 1]" << std::endl;

    std::cout
        << argv[1] << ","
        << argv[2] << ","
        << argv[3] << ","
        << argv[4] << ","
        << argv[5] << ","
        << argv[6] << ","
        << argv[7] << ",";

    red.test();

    return 0;
}

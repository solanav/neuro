#include <iostream>
#include <fstream>
#include <map>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"

int main(int argc, char *argv[])
{
    std::vector<std::tuple<float, size_t, Neurona::Tipo>> neurona_descriptor {
        {1, 3, Neurona::Tipo::McCulloch},
        {2, 3, Neurona::Tipo::McCulloch},
        {1, 1, Neurona::Tipo::McCulloch},
    };

    RedNeuronal red_test = RedNeuronal(neurona_descriptor, false);

    float peso = 1;

    // Conectamos las neuronas
    red_test.conectar(0, 0, 1, 0, peso);
    red_test.conectar(0, 0, 1, 2, peso);
    red_test.conectar(0, 1, 1, 0, peso);
    red_test.conectar(0, 1, 1, 1, peso);
    red_test.conectar(0, 2, 1, 1, peso);
    red_test.conectar(0, 2, 1, 2, peso);
    red_test.conectar(1, 0, 2, 0, peso);
    red_test.conectar(1, 1, 2, 0, peso);
    red_test.conectar(1, 2, 2, 0, peso);

    std::ifstream infile("inputs/entradas.txt");
    std::ofstream output;
    output.open("results_mp.txt");
    float a, b, c;

    output << "x1\tx2\tx3\t\ta12\ta23\ta13\t\ty" << std::endl;
    while (infile >> a >> b >> c)
    {
        std::vector<float> inputs = {a, b, c};
        red_test.step(inputs);

        output
            << red_test.capas[0].neuronas[0]->f_x << "\t"
            << red_test.capas[0].neuronas[1]->f_x << "\t"
            << red_test.capas[0].neuronas[2]->f_x << "\t\t"
            << red_test.capas[1].neuronas[0]->f_x << "\t"
            << red_test.capas[1].neuronas[1]->f_x << "\t"
            << red_test.capas[1].neuronas[2]->f_x << "\t\t"
            << red_test.capas[2].neuronas[0]->f_x << std::endl;

        red_test.print();
        red_test.print_dot("test.dot");
        getchar();
    }

    for (int i = 0; i < red_test.capas.size() - 1; i++)
    {
        std::vector<float> inputs = {0, 0, 0};
        red_test.step(inputs);

        output
            << "-\t-\t-\t\t"
            << red_test.capas[1].neuronas[0]->f_x << "\t"
            << red_test.capas[1].neuronas[1]->f_x << "\t"
            << red_test.capas[1].neuronas[2]->f_x << "\t\t"
            << red_test.capas[2].neuronas[0]->f_x << std::endl;
    }

    return 0;
}
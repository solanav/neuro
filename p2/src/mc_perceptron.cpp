#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"
#include "lector.h"
#include "math.h"

int main(int argc, char const *argv[])
{
    float tasa_ap = 1;
    float umbral = 0.2;
    int num_oculta = 2 + 1;

    Lector l = Lector();
    l.leer2((char *)"inputs/and.txt");

    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas + 1; // Tenemos en cuenta el sesgo
    int num_salidas = l.num_salidas;

    std::vector<std::tuple<float, size_t, Neurona::Tipo>> descriptor {
        {umbral, num_entradas - 1, Neurona::Directa},
        {umbral, num_oculta - 1, Neurona::SigmoideBipolar},
        {umbral, num_salidas, Neurona::SigmoideBipolar},
    };

    RedNeuronal red = RedNeuronal(descriptor, true);
    red.conectar(PESO_PEQUENO);

    int epoch = 0;

    red.print();
    red.print_dot("test.dot");

    bool cont = true;
    //Paso 1
    while (cont)
    {
        red.print();
        red.print_dot("test.dot");

        red.next(l.entradas_entrenamiento[0]);

        auto error_l = red.capas[2].error(l.salidas_entrenamiento[0]);
        for (int j = 0; j < num_neuronas; j++)
        {
            error += 
        }

        std::cout  << "\n\nEpoch: "<< epoch << std::endl;
        epoch ++;

        getchar();
    }
    
    return 0;
}

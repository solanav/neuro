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

int main(int argc, char *argv[])
{

    if(argc < 6){
        std::cout << "Uso: ./(exe) (fichero datos) (modo) (umbral) (tasa de aprendizaje) (porcentaje o fichero de test, segun modo)" << std::endl;
        return -1;
    }

    int modo = std::stoi(argv[2]);

    std::ifstream f(argv[1]);
    if(!f.good()){
        std::cout << "Archivo no existe" << std::endl;
        return -1;
    }

    Lector l;
    if(modo == 1)
        l.leer1(argv[1], std::stof(argv[5]));
    else if(modo == 2)
        l.leer2(argv[1]);
    else if(modo == 3)
        l.leer3(argv[1], argv[5]);
    else
    {
        std::cout << "Modo inválido" << std::endl;
    }

    // Lo sacamos del lector
    int num_rows_entrenamiento = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas + 1;
    int num_salidas = l.num_salidas;

    // Establecemos la tasa de aprendizaje
    float tasa_aprendizaje = std::stof(argv[4]);

    // Setup de la red
    float umbral = std::stof(argv[3]);
    Neurona *entrada_raw = (Neurona *) calloc(num_entradas, sizeof(Neurona));
    Neurona *salida_raw = (Neurona *) calloc(num_salidas, sizeof(Neurona));

    // Creamos la capa de entrada
    Capa capa_entrada = Capa();
    entrada_raw[0] = Neurona(umbral, Neurona::Tipo::Sesgo);
    capa_entrada.Anadir(&(entrada_raw[0]));
    for (int i = 1; i < num_entradas; i++)
    {
        entrada_raw[i] = Neurona(umbral, Neurona::Tipo::Directa);
        capa_entrada.Anadir(&(entrada_raw[i]));
    }

    // Creamos la capa de salida
    Capa capa_salida = Capa();
    for (int i = 0; i < num_salidas; i++)
    {
        salida_raw[i] = Neurona(umbral, Neurona::Tipo::Perceptron);
        capa_salida.Anadir(&(salida_raw[i]));
    }

    // Conectamos las dos capas
    capa_entrada.Conectar(&capa_salida, PESO_CERO);

    RedNeuronal red = RedNeuronal();
    red.Anadir(&capa_entrada);
    red.Anadir(&capa_salida);

    // Entrenamiento
    bool cont = true;
    while (cont)
    {
        // Por cada row de entrenamiento
        cont = false;
        for (int i = 0; i < num_rows_entrenamiento; i++)
        {
            std::vector<float> entrada = l.entradas_entrenamiento[i];
            std::vector<float> salida = l.salidas_entrenamiento[i];

            // Metemos la entrada como valor de las neuronas
            for (int j = 1; j < num_entradas; j++)
                entrada_raw[j].inicializar(entrada[j - 1]);

            // Disparamos y propagamos la entrada
            red.Disparar();
            red.Inicializar();
            red.Propagar();

            // Ahora que valor esta en Y, disparamos Y para sacar f_x
            red.capas[1]->Disparar();

            // red.print();
            // std::cout << "\n" << std::endl;

            // Iteramos por todas las neuronas de salida
            for (int j = 0; j < num_salidas; j++)
            {
                std::cout << "y_in " << salida_raw[j].valor << std::endl;
                // Calculamos nuestra salida (y) y la salida real (t)
                float y = salida_raw[j].f_x;
                float t = salida[j];

                std::cout << "[" << entrada[0] << " and " << entrada[1] << " = " << y << "] ?= " << t << std::endl;

                // Si la salida es incorrecta
                if (y != t)
                {
                    // Seguimos entrenando
                    cont = true;

                    // Actualizamos el sesgo
                    float old_sesgo = entrada_raw[0].conexiones[j].peso;
                    entrada_raw[0].conexiones[j].peso_anterior = old_sesgo;

                    float new_sesgo = old_sesgo + (tasa_aprendizaje * t);
                    entrada_raw[0].conexiones[j].peso = new_sesgo;

                    // Actualizamos pesos (y seguimos entrenando)
                    for (int k = 1; k < num_entradas; k++)
                    {
                        // Actualizamos el peso
                        float old_peso = entrada_raw[k].conexiones[j].peso;
                        entrada_raw[k].conexiones[j].peso_anterior = old_peso;

                        float new_peso = old_peso + (tasa_aprendizaje * t * entrada[k - 1]);
                        entrada_raw[k].conexiones[j].peso = new_peso;

                        std::cout << "Nuevo peso de " << &(entrada_raw[k].conexiones[j]) << " >> " << old_peso << " + (" << tasa_aprendizaje << " * " << t << " * " << entrada[k - 1] << ") = "<< new_peso << std::endl;
                    }

                    std::cout << "Nuevo sesgo >> " << old_sesgo << " + (" << tasa_aprendizaje << " * " << t << ") = "<< new_sesgo << std::endl;
                } else {
                    std::cout << "\n" << std::endl;
                }
            }

            // std::cout << ">> Press enter <<" << std::endl;
            // getchar();
        }
    }

    int hits = 0;
    int misses = 0;
    float ecm = 0;

    for (int i = 0; i < num_rows_test; i++)
    {
        std::vector<float> entradat = l.entradas_test[i];
        std::vector<float> salidat = l.salidas_test[i];

        for (int j = 0; j < num_entradas; j++)
            entrada_raw[j].inicializar(entradat[j - 1]);

        red.Disparar();
        red.Inicializar();
        red.Propagar();

        // Ahora que valor esta en Y, disparamos Y para sacar f_x
        red.capas[1]->Disparar();

        for (int j = 0; j < num_salidas; j++)
        {
            float y = salida_raw[j].f_x;

            ecm += pow(y - salidat[j], 2);

            //std::cout << y << "\t?=\t" << salidat[j] << std::endl;
            if(y == salidat[j])
                hits++;
            else
                misses++;
        }
    }

    float hit_per = float(hits) / float(hits + misses);

    std::cout << "HITS: " << hits << std::endl << "MISSES: " << misses << std::endl;
    std::cout << "HIT%: " << hit_per * 100 << "%" << std::endl;
    std::cout << "ECM:  " << ecm / float(hits + misses) << std::endl;

    free(entrada_raw);
    free(salida_raw);

    return 0;
}
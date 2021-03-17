#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"
#include "lector.h"

int f(float y, int umbral)
{
    int f_x;

    if (y > umbral)
        f_x = 1;
    else if (y < -umbral)
        f_x = -1;
    if (y <= umbral && y >= -umbral)
        f_x = 0;

    return f_x;
}

int main(int argc, char *argv[])
{
    Lector l;
    l.leer1((char *) "and.txt", 0.5);

    // Lo sacamos del lector
    int num_rows_entrenamiento = l.entradas_entrenamiento.size();
    int num_entradas = l.num_entradas;
    int num_salidas = l.num_salidas;

    // Establecemos la tasa de aprendizaje
    float tasa_aprendizaje = 0.02;

    // Setup de la red
    float umbral = 2;
    Neurona *entrada_raw = (Neurona *) calloc(num_entradas, sizeof(Neurona));
    Neurona *salida_raw = (Neurona *) calloc(num_salidas, sizeof(Neurona));

    // Creamos la capa de entrada
    Capa capa_entrada = Capa();
    for (int i = 0; i < num_entradas; i++)
    {
        entrada_raw[i] = Neurona(umbral, Neurona::Tipo::Sesgo);
        capa_entrada.Anadir(&(entrada_raw[i]));
    }

    // Creamos la capa de salida
    Capa capa_salida = Capa();
    for (int i = 0; i < num_salidas; i++)
    {
        salida_raw[i] = Neurona(umbral, Neurona::Tipo::Sesgo);
        capa_salida.Anadir(&(salida_raw[i]));
    }

    // Conectamos las dos capas
    capa_entrada.Conectar(&capa_salida, PESO_PEQUENO);

    RedNeuronal red = RedNeuronal();
    red.Anadir(&capa_entrada);
    red.Anadir(&capa_salida);

    // Entrenamiento
    bool cont = true;
    while (cont)
    {
        // Por cada row de entrenamiento
        for (int i = 0; i < num_rows_entrenamiento; i++)
        {
            std::vector<float> entrada = l.entradas_entrenamiento[i];
            std::vector<float> salida = l.salidas_entrenamiento[i];

            for (int j = 0; j < num_entradas; j++)
                entrada_raw[j].inicializar(entrada[j]);

            red.print();
            std::cout << "\n" << std::endl;
            usleep(10000);

            red.Disparar();
            red.Inicializar();
            red.Propagar();

            // Iteramos por todas las neuronas de salida
            cont = false;
            for (int j = 0; j < num_salidas; j++)
            {
                float y = f(salida_raw[j].valor, umbral);
                float t = salida[j];

                // Actualizamos pesos (y seguimos entrenando)
                for (int k = 0; k < num_entradas; k++)
                {
                    // Actualizamos el peso
                    float old_peso = entrada_raw[k].conexiones[j].peso;
                    entrada_raw[k].conexiones[j].peso_anterior = old_peso;

                    float new_peso = old_peso + (tasa_aprendizaje * (t-y) * entrada[k]);
                    entrada_raw[k].conexiones[j].peso = new_peso;

                    // Actualizamos el sesgo
                    entrada_raw[k].sesgo = entrada_raw[k].sesgo + (tasa_aprendizaje * (t-y));

                    // Seguimos si los pesos han cambiado
                    if (abs(new_peso - old_peso) > tolerancia_peso)
                        cont = true;
                }

                std::cout << y << " ?= " << t << std::endl;
            }
        }
    }

    free(entrada_raw);
    free(salida_raw);

    return 0;
}
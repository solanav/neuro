#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"
#include "lector.h"

int main(int argc, char *argv[])
{

    Lector l;
    l.leer2((char *) "and.txt");

    // Lo sacamos del lector
    int num_rows_entrenamiento = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas + 1;
    int num_salidas = l.num_salidas;

    // Establecemos la tasa de aprendizaje
    float tasa_aprendizaje = 1;

    // Setup de la red
    float umbral = 0.2;
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
            std::cout << "\n" << std::endl;

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

    for (int i; i < num_rows_test; i++)
    {
        std::vector<float> entrada = l.entradas_test[i];
        std::vector<float> salida = l.salidas_test[i];

        for (int j = 0; j < num_entradas; j++)
            entrada_raw[j].inicializar(entrada[j - 1]);

        red.Disparar();
        red.Inicializar();
        red.Propagar();

        // Ahora que valor esta en Y, disparamos Y para sacar f_x
        red.capas[1]->Disparar();

        for (int j = 0; j < num_salidas; j++)
        {
            float y = salida_raw[j].f_x;
            std::cout << entrada[0] << " and " << entrada[1] << " = " << y << " ?= " << salida[j] << std::endl;
        }
    }

    free(entrada_raw);
    free(salida_raw);

    return 0;
}
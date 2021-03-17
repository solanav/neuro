#include <iostream>
#include <fstream>

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
    int umbral = 1;
    std::vector<Neurona> entrada_raw = std::vector<Neurona>();
    std::vector<Neurona> salida_raw = std::vector<Neurona>();

    Capa capa_entrada = Capa();
    for (int i = 0; i < num_entradas; i++)
    {
        Neurona tmp = Neurona(umbral, Neurona::Tipo::Sesgo);
        entrada_raw.push_back(tmp);
        capa_entrada.Anadir(&tmp);
    }

    Capa capa_salida = Capa();
    for (int i = 0; i < num_salidas; i++)
    {
        Neurona tmp = Neurona(umbral, Neurona::Tipo::Sesgo);
        salida_raw.push_back(tmp);
        capa_salida.Anadir(&tmp);
    }

    capa_entrada.Conectar(&capa_salida, PESO_CERO);

    RedNeuronal red = RedNeuronal();
    red.Anadir(&capa_entrada);
    red.Anadir(&capa_salida);

    // Entrenamiento
    bool cont = true;
    while (cont)
    {
        for (int i = 0; i < num_rows_entrenamiento; i++)
        {
            std::vector<float> entrada = l.entradas_entrenamiento[i];
            std::vector<float> salida = l.salidas_entrenamiento[i];

            for (int j = 0; j < num_entradas; j++)
                entrada_raw[j].inicializar(entrada[j]);

            std::cout << entrada_raw[1].tipo << std::endl;

            red.Disparar();
            red.Inicializar();
            red.Propagar();

            // Imprimimos la salida
            for (int j = 0; j < num_salidas; j++)
            {
                float y = f(salida_raw[j].valor, umbral);
                float t = salida[j];

                if (y != t)
                {
                    for (int k = 0; k < num_entradas; k++)
                    {
                        // Actualizamos el peso
                        float old_peso = entrada_raw[k].conexiones[j].peso;
                        entrada_raw[k].conexiones[j].peso_anterior = old_peso;

                        float new_peso = old_peso + (tasa_aprendizaje * t * entrada[k]);
                        entrada_raw[k].conexiones[j].peso = new_peso;

                        // Actualizamos el sesgo
                        entrada_raw[k].sesgo = entrada_raw[k].sesgo + (tasa_aprendizaje * t);
                    }
                }

                std::cout << y << " ?= " << t << std::endl;
            }
        }

        cont = false;
    }

    return 0;
}
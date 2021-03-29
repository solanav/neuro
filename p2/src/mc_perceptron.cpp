#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"
#include "lector.h"

float retropropagacion(float f_x) {
    return 0.5 * (1 + f_x) * (1 - f_x);
}

int main(int argc, char const *argv[])
{
    float tasa_ap = 0.1;
    float umbral = 0.2;
    int num_oculta = 2 + 1;

    Lector l = Lector();
    l.leer2("inputs/and.txt");

    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas + 1; // Tenemos en cuenta el sesgo
    int num_salidas = l.num_salidas;

    std::vector<std::tuple<float, size_t, Neurona::Tipo>> descriptor {
        {umbral, num_entradas - 1, Neurona::Directa},
        {umbral, num_oculta - 1, Neurona::SigmoideBipolar},
        {umbral, num_salidas, Neurona::SigmoideBipolar},
    };

    //Paso 0
    RedNeuronal red = RedNeuronal(descriptor, true);
    red.conectar(PESO_PEQUENO);

    //red.print();
    red.print_dot("test.dot");

    // Main loop (pseudocode)
    /*  i = neuronas entrada
        j = neuronas oculta
        k = neuronas salida
        */



    bool cont = true;
    //Paso 1
    while (cont)
    {
        //Paso 2
        for(int train=0; train < num_rows_train; train++) {
            std::vector<float> entrada = l.entradas_entrenamiento[train];
            std::vector<float> salida = l.salidas_entrenamiento[train];
            //Feedforward
            //Paso 3, 4 y 5
            red.next(entrada);
            cont = false;
            
            //Retropropagacion - Esto es lo guapo
            //Paso 6
            std::vector<float> delta_s = std::vector<float>();
            std::vector<std::vector<float>> delta_peso_os = std::vector<std::vector<float>>();
            for (int j = 0; j < num_oculta; j++)
            {
                    delta_peso_os[j] = std::vector<float>();
            }
            
            for(int k = 0; k < num_salidas; k++) {
                delta_s[k] = (salida[k] - red.capas[0].neuronas[k]->f_x)*(retropropagacion(red.capas[0].neuronas[k]->f_x));
                
                for(int j = 1; j < num_oculta; j++){
                    delta_peso_os[j][k] = tasa_ap * delta_s[k] * red.capas[1].neuronas[j]->f_x ;
                }
                
                // Sesgo
                delta_peso_os[0][k] = tasa_ap * delta_s[k];
            }

            //Paso 7
            std::vector<std::vector<float>> delta_peso_eo = std::vector<std::vector<float>>();
            for(int i = 0; i < num_entradas; i++){
                delta_peso_eo[i] = std::vector<float>();
            }
            for(int j = 1; j < num_oculta; j++) {
                float delta_in = 0;

                for (int k; k < num_salidas; k++) {
                    delta_in += delta_s[k] * red.capas[1].neuronas[j]->conexiones[k].peso;
                }

                float delta_o = delta_in * retropropagacion(red.capas[1].neuronas[j]->f_x);

                for(int i = 1; i < num_entradas; i++) {
                    delta_peso_eo[i][j] = tasa_ap * delta_o * red.capas[0].neuronas[i]->f_x;
                }

                delta_peso_eo[0][j] = tasa_ap * delta_o;
            }

            // Paso 8
            for(int k = 0; k < num_salidas; k++){
                for(int j = 0; j < num_oculta; j ++){
                    float old_peso = red.capas[1].neuronas[j]->conexiones[k].peso;
                    red.capas[1].neuronas[j]->conexiones[k].peso_anterior = old_peso;

                    red.capas[1].neuronas[j]->conexiones[k].peso = old_peso + delta_peso_os[j][k];
                }
            }

            for(int j = 1; j < num_oculta; j++){
                for(int i = 0; i < num_entradas; i++){
                    float old_peso = red.capas[0].neuronas[i]->conexiones[j].peso;
                    red.capas[0].neuronas[i]->conexiones[j].peso_anterior = old_peso;

                    red.capas[0].neuronas[i]->conexiones[j].peso = old_peso + delta_peso_eo[i][j];
                }
            }

            // Paso 9
            cont = false;
        }
    }
    
    red.print();
    return 0;
}

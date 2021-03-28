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
    std::vector<std::tuple<float, size_t, Neurona::Tipo>> descriptor {
        {0.2, 2, Neurona::Directa},
        {0.2, 2, Neurona::SigmoideBipolar},
        {0.2, 1, Neurona::SigmoideBipolar},
    };
    
    //Paso 0
    RedNeuronal red = RedNeuronal(descriptor, true);
    red.conectar(PESO_PEQUENO);
    int tasa_ap = 0.1;

    red.print();
    red.print_dot("test.dot");

    // Main loop (pseudocode)
    /*  i = neuronas entrada
        j = neuronas oculta
        k = neuronas salida
    //Paso 1
    while (stop condition)
    {
        //Paso 2
        for(each train) {
            //Feedforward
            //Paso 3
            for (i){
                neurona = train_entrada[i]
            }

            //Paso 4 - Calcular respuesta de neuronas de capa oculta

            red.step()

            //Paso 5 - Calcular respuesta de salida

            red.step()

            //Retropropagacion - Esto es lo guapo
            //Paso 6
            for(k) {
                delta_s[k] = (objetivo[k] - neurona[k]->f_x)*(retropropagacion(neurona[k]->f_x)) 
                
                for(j){
                    delta_peso_os[j][k] = tasa_ap * delta_s[k] * neurona[j]->f_x 
                }
                
                delta_sesgo_oculta[k] = tasa_ap * delta_s[k]
            }

            //Paso 7
            for(j) {
                delta_in[j] = 0
                for (k) {
                    delta_in[j] += delta_s[k] neurona[j]->conexion[k]->peso
                }

                delta_o[j] = delta_in[j] * retropropagacion(neurona[j]->f_x)

                for(i) {
                    delta_peso_eo[i][j] = tasa_ap * delta_o[j] * neurona[i]-> f_x
                }

                delta_sesgo_entrada[j] = tasa_ap * delta_o[j]
            }

            // Paso 8
            for(k){
                for(j){
                    neurona[j]->conexion[k]->peso_anterior = neurona[j]->conexion[k]->peso

                    neurona[j]->conexion[k]->peso = old_peso + delta_peso_os[j][k]
                }
            }

            for(j){
                for(i){
                    neurona[i]->conexion[j]->peso_anterior = neurona[i]->conexion[j]->peso

                    neurona[i]->conexion[j]->peso = old_peso + delta_peso_eo[i][j]
                }
            }

            // Paso 9
            comprobar y actualizar condicion de parada
        }
        
    }
    
    */

    return 0;
}

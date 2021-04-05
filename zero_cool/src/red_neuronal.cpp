#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>

#include "red_neuronal.h"
#include "mates.h"
#include "progressbar.h"

RedNeuronal::RedNeuronal(size_t num_oculta, float tasa_aprendizaje, int bi, Lector l, const char* output_file_name, int max_epocas)
{
    this->bi = bi;
    this->tasa_aprendizaje = tasa_aprendizaje;
    output_file.open(output_file_name, std::ios::app);
    this->l = l;
    this->max_epocas = max_epocas;

    // Cambiamos algun nombre
    int num_entrada = this->l.num_entradas;
    int num_salida = this->l.num_salidas;

    // Inicializamos las capas a ceros
    capa_entrada     = std::vector<float>(num_entrada, 0);
    capa_oculta      = std::vector<float>(num_oculta, 0);
    capa_oculta_tmp  = std::vector<float>(num_oculta, 0);
    capa_salida      = std::vector<float>(num_salida, 0);
    capa_salida_tmp  = std::vector<float>(num_salida, 0);

    // Metemos numeros al azar en los pesos
    for (int i = 0; i < num_oculta; i++)
    {
        std::vector<float> tmp;
        for (int j = 0; j < num_entrada; j++)
            tmp.push_back(random_number(-0.5, 0.5));
        eo_peso.push_back(tmp);
    }

    for (int i = 0; i < num_salida; i++)
    {
        std::vector<float> tmp;
        for (int j = 0; j < num_oculta; j++)
            tmp.push_back(random_number(-0.5, 0.5));
        os_peso.push_back(tmp);
    }

    // Ponemos el bias a lo que sea
    eo_sesgo = std::vector<float>(num_oculta, 0);
    os_sesgo = std::vector<float>(num_salida, 0);

    /* ESTO ES EL EJEMPLO DE LAS PRESENTACIONES
    
    eo_peso = {
        {0.7, -0.2},
        {-0.4, 0.3},
    };

    eo_sesgo = {0.4, 0.6};

    os_peso = {
        {0.5, 0.1},
    };

    os_sesgo = {-0.3};*/
}

RedNeuronal::~RedNeuronal() {
    output_file.close();
}

void RedNeuronal::print()
{
    std::cout << "Capa de entrada ======================" << std::endl;
    print_tensor(capa_entrada);
    
    std::cout << "Pesos y sesgos primeros ==============" << std::endl;
    print_tensor(eo_peso);
    print_tensor(eo_sesgo);

    std::cout << "Capa oculta ==========================" << std::endl;
    print_tensor(capa_oculta);
    
    std::cout << "Pesos y sesgos segundos ==============" << std::endl;
    print_tensor(os_peso);
    print_tensor(os_sesgo);
    
    std::cout << "Capa de salida =======================" << std::endl;
    print_tensor(capa_salida);
}

void RedNeuronal::feedforward(std::vector<float> entrada)
{
    // Copy training data to capa de entrada
    capa_entrada = entrada;

    // Dot product of entrada and peso and then add the bias
    capa_oculta_tmp = add_tensors(dot_product(capa_entrada, eo_peso), eo_sesgo);

    // Aplicamos la funcion a la capa oculta
    capa_oculta = sigmoide(capa_oculta_tmp, bi);

    // Dot product of oculta and peso and then add the bias
    capa_salida_tmp = add_tensors(dot_product(capa_oculta, os_peso), os_sesgo);

    // Aplicamos la funcion a la salida
    capa_salida = sigmoide(capa_salida_tmp, bi);
}

void RedNeuronal::aprender(std::vector<float> results)
{
    // Calculamos delta de la neurona de salida
    std::vector<float> diff = sub_tensors(results, capa_salida);
    std::vector<float> delta_salida(capa_salida.size());
    for (int k = 0; k < capa_salida.size(); k++)
        delta_salida[k] = diff[k] * sigmoide_der(capa_salida_tmp[k], bi);

    // Calculamos la actualizacion de peso de oculta-salida
    std::vector<std::vector<float>> delta_w(
        capa_salida.size(),
        std::vector<float>(capa_oculta.size())
    );
    for (int j = 0; j < capa_oculta.size(); j++)
        for (int k = 0; k < capa_salida.size(); k++)
            delta_w[k][j] = tasa_aprendizaje * delta_salida[k] * capa_oculta[j];

    // Calculamos la actualizacion de sesgo oculta-salida
    std::vector<float> delta_sw(capa_salida.size());
    for (int k = 0; k < capa_salida.size(); k++)
        delta_sw[k] = tasa_aprendizaje * delta_salida[k];

    // Calculamos el delta intermedio
    std::vector<float> delta_in(capa_oculta.size(), 0);
    for (int j = 0; j < capa_oculta.size(); j++)
        for (int k = 0; k < capa_salida.size(); k++)
            delta_in[j] += delta_salida[k] * os_peso[k][j];

    // Calculamos el delta de la oculta
    std::vector<float> delta_oculta(capa_oculta.size());
    for (int j = 0; j < capa_oculta.size(); j++)
        delta_oculta[j] = delta_in[j] * sigmoide_der(capa_oculta_tmp[j], bi);

    // Calculamos la correccion del peso de la oculta
    std::vector<std::vector<float>> delta_v(
        capa_oculta.size(),
        std::vector<float>(capa_entrada.size())
    );
    for (int i = 0; i < capa_entrada.size(); i++)
        for (int j = 0; j < capa_oculta.size(); j++)
            delta_v[j][i] = tasa_aprendizaje * delta_oculta[j] * capa_entrada[i];

    // Calculamos la actualizacion de sesgo entrada-oculta
    std::vector<float> delta_sv(capa_oculta.size());
    for (int j = 0; j < capa_oculta.size(); j++)
        delta_sv[j] = tasa_aprendizaje * delta_oculta[j];

    // Actualizamos los pesos sumando los deltas
    eo_peso = add_tensors(eo_peso, delta_v);
    os_peso = add_tensors(os_peso, delta_w);

    // Actualizamos los sesgos sumando los deltas
    eo_sesgo = add_tensors(eo_sesgo, delta_sv);
    os_sesgo = add_tensors(os_sesgo, delta_sw);
}

void RedNeuronal::train()
{
    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas;
    int num_salidas = l.num_salidas;

    int epocas = 0;
    progressbar bar(max_epocas);
    for (; epocas < max_epocas; epocas++)
    {
        bar.update();

        std::vector<float> error_cuadratico_medio(num_salidas, 0);
        
        // Entrenamiento
        for (int i = 0; i < num_rows_train; i++)
        {
            feedforward(l.entradas_entrenamiento[i]);
            aprender(l.salidas_entrenamiento[i]);

            for (int j = 0; j < num_salidas; j++)
                error_cuadratico_medio[j] += pow(capa_salida[j] - l.salidas_entrenamiento[i][j], 2);
        }

        // Terminamos de hacer la media
        for (int i = 0; i < num_salidas; i++)
            error_cuadratico_medio[i] /= num_rows_test;

        // Comprobamos que todo va bien
        if (error_cuadratico_medio[0] < 0.01)
            break;
    }
    std::cout << std::endl;
    std::cout << "Epocas: " << epocas << std::endl;
}

void RedNeuronal::test()
{
    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_entradas = l.num_entradas;
    int num_salidas = l.num_salidas;
    
    // Testing
    std::vector<float> error_cuadratico_medio(num_salidas, 0);
    for (int i = 0; i < num_rows_test; i++)
    {
        feedforward(l.entradas_test[i]);
        for (int j = 0; j < num_salidas; j++)
            error_cuadratico_medio[j] += pow(capa_salida[j] - l.salidas_test[i][j], 2);
    }

    // Terminamos de hacer la media
    for (int i = 0; i < num_salidas; i++)
        error_cuadratico_medio[i] /= num_rows_test;

    output_file
        << capa_oculta.size() << ","
        << error_cuadratico_medio[0] << ","
        << bi << ","
        << tasa_aprendizaje
        << std::endl;
    
    std::cout
        << "capa_oculta: " << capa_oculta.size() << "\n"
        << "error_cuadratico_medio: " << error_cuadratico_medio[0] << "\n"
        << "bi: " << bi << "\n"
        << "tasa_aprendizaje: " << tasa_aprendizaje
        << std::endl;
}


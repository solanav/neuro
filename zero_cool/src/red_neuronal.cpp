#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <chrono>
#include <algorithm>

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

void RedNeuronal::aprender2(std::vector<float> results)
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

    // Guardamos los deltas de los pesos
    delta_v_all.push_back(delta_v);
    delta_w_all.push_back(delta_w);

    // Guardamos los deltas de los sesgos
    delta_sv_all.push_back(delta_sv);
    delta_sw_all.push_back(delta_sw);
}

void RedNeuronal::train()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::srand (unsigned (std::time(0)));

    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_salidas = l.num_salidas;

    int epocas = 0;
    //progressbar bar(max_epocas);
    for (; epocas < max_epocas; epocas++)
    {
        //bar.update();

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

        std::cout << error_cuadratico_medio[0] << std::endl;

        /* Comprobamos que todo va bien
        if (error_cuadratico_medio[0] < 0.01)
            break;*/
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << std::endl;
    std::cout << "Epocas: " << epocas << std::endl;
    std::cout << "Tiempo: " << (double) duration.count() / (double) 1000000 << std::endl;
}

void RedNeuronal::train2()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::srand (unsigned (std::time(0)));

    int num_rows_train = l.entradas_entrenamiento.size();
    int num_rows_test = l.entradas_test.size();
    int num_salidas = l.num_salidas;

    int epocas = 0;
    //progressbar bar(max_epocas);
    for (; epocas < max_epocas; epocas++)
    {
        //bar.update();

        std::vector<float> error_cuadratico_medio(num_salidas, 0);

        // Acumulamos los deltas de los pesos
        for (int i = 0; i < num_rows_train; i++)
        {
            feedforward(l.entradas_entrenamiento[i]);
            aprender2(l.salidas_entrenamiento[i]);

            for (int j = 0; j < num_salidas; j++)
                error_cuadratico_medio[j] += pow(capa_salida[j] - l.salidas_entrenamiento[i][j], 2);
        }

        // Gradient descent
        gradient_descent();

        // Terminamos de hacer la media
        for (int i = 0; i < num_salidas; i++)
            error_cuadratico_medio[i] /= num_rows_test;

        std::cout << error_cuadratico_medio[0] << std::endl;

        /* Comprobamos que todo va bien
        if (error_cuadratico_medio[0] < 0.01)
            break;*/

        // Reduce the learning rate
        //tasa_aprendizaje -= tasa_aprendizaje * 1/max_epocas;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << std::endl;
    std::cout << "Epocas: " << epocas << std::endl;
    std::cout << "Tiempo: " << (double) duration.count() / (double) 1000000 << std::endl;
    std::cout << "Tasa  : " << tasa_aprendizaje << std::endl;
}

void RedNeuronal::gradient_descent()
{
    // Correct entrada-oculta pesos
    auto delta_v_average = average_tensors(delta_v_all);
    eo_peso = add_tensors(eo_peso, delta_v_average);

    // Correct oculta-salida pesos
    auto delta_w_average = average_tensors(delta_w_all);
    os_peso = add_tensors(os_peso, delta_w_average);

    // Correct entrada-oculta sesgos
    auto delta_sv_average = average_tensors(delta_sv_all);
    eo_sesgo = add_tensors(eo_sesgo, delta_sv_average);

    // Correct oculta-salida sesgos
    auto delta_sw_average = average_tensors(delta_sw_all);
    os_sesgo = add_tensors(os_sesgo, delta_sw_average);

    // Clean all learning variables, we are starting a new epoch
    delta_v_all.clear();
    delta_w_all.clear();
    delta_sv_all.clear();
    delta_sw_all.clear();
}

void RedNeuronal::test()
{
    int num_rows_test = l.entradas_test.size();
    int num_salidas = l.num_salidas;

    int tp = 0;
    int fp = 0;
    int fn = 0;
    int tn = 0;
    
    // Testing
    std::vector<float> error_cuadratico_medio(num_salidas, 0);
    for (int i = 0; i < num_rows_test; i++)
    {
        feedforward(l.entradas_test[i]);

        for (int j = 0; j < num_salidas; j++)
            error_cuadratico_medio[j] += pow(capa_salida[j] - l.salidas_test[i][j], 2);

        std::vector<float> output(num_salidas);
        for (int j = 0; j < num_salidas; j++)
        {
            output[j] = capa_salida[j] >= 0.5 ? 1 : 0;

            auto prediction = output[j];
            auto reality = l.salidas_test[i][j];

            if (prediction == 1 and reality == 1)
                tp++;
            else if (prediction == 1 and reality == 0)
                fp++;
            else if (prediction == 0 and reality == 0)
                tn++;
            else if (prediction == 0 and reality == 1)
                fn++;
        }

        // print_tensor(l.entradas_test[i]);
        // print_tensor(l.salidas_test[i]);
        // print_tensor(output);
        // print_tensor(capa_salida);
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
    
    auto aciertos = (tp + tn) / num_salidas;

    std::cout
        << error_cuadratico_medio[0] << ","
        << tp << ","
        << fp << ","
        << fn << ","
        << tn << ","
        << ((float) aciertos / (float) num_rows_test) * 100.0 << "\n\n"
        << std::endl;

    std::cout
        << "capa_oculta: " << capa_oculta.size() << "\n"
        << "error_cuadratico_medio: " << error_cuadratico_medio[0] << "\n"
        << "bi: " << bi << "\n"
        << "tasa_aprendizaje: " << tasa_aprendizaje << "\n"
        << "matriz de confusion: " << "\n"
        << "| " << tp << " | " << fp << " |" << "\n"
        << "| " << fn << " | " << tn << " |" << "\n"
        << "aciertos: " << ((float) aciertos / (float) num_rows_test) * 100.0 << "%"
        << std::endl;
}


#ifndef RED_NEURONAL_H
#define RED_NEURONAL_H

#include <vector>
#include <iostream>
#include <fstream>

#include "lector.h"

class RedNeuronal {
public:
    RedNeuronal(size_t num_oculta, float tasa_aprendizaje, int bi, Lector l, const char* output_file_name, int max_epocas);
    virtual ~RedNeuronal();
    void feedforward(std::vector<float> entrada);
    void print();
    void aprender(std::vector<float> results);
    void train();
    void test();

private:
    // User provided data
    float tasa_aprendizaje;
    int bi;
    Lector l;
    std::ofstream output_file;
    int max_epocas;

    // Internal data
    std::vector<float> capa_entrada;
    
    std::vector<std::vector<float>> eo_peso;
    std::vector<float> eo_sesgo;
    
    std::vector<float> capa_oculta;
    std::vector<float> capa_oculta_tmp; // Salida sin pasar por f(x) o f'(x)

    std::vector<std::vector<float>> os_peso;
    std::vector<float> os_sesgo;
    
    std::vector<float> capa_salida;
    std::vector<float> capa_salida_tmp; // Salida sin pasar por f(x) o f'(x)
};

#endif
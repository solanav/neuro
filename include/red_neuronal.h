#ifndef RED_NEURONAL_H
#define RED_NEURONAL_H

#include <vector>
#include "capa.h"

class RedNeuronal {
public:
    RedNeuronal();
    RedNeuronal(float umbral, std::vector<std::tuple<size_t, Neurona::Tipo>> neuronas);
    virtual ~RedNeuronal();
    void Inicializar();
    void Anadir(Capa capa);
    void Disparar();
    void Propagar();
    void step(std::vector<float> inputs);
    void conectar(int capa_x, int neurona_x, int capa_y, int neurona_y, float peso);
    void print_dot(std::string file_name);
    std::tuple<size_t, size_t> find(std::shared_ptr<Neurona> neurona);
    void print();

public:
    std::vector<Capa> capas;
};

#endif
#ifndef RED_NEURONAL_H
#define RED_NEURONAL_H

#include <vector>
#include "capa.h"

class RedNeuronal {
public:
    RedNeuronal();
    RedNeuronal(std::vector<std::tuple<float, size_t, Neurona::Tipo>> neuronas, bool sesgo);
    virtual ~RedNeuronal();
    void Inicializar();
    void Anadir(Capa capa);
    void Disparar();
    void Propagar();
    void step(std::vector<float> inputs);
    void next(std::vector<float> inputs);
    void conectar(int modo_peso);
    void conectar(int capa_x, int neurona_x, int capa_y, int neurona_y, float peso);
    void print_dot(std::string file_name);
    std::tuple<size_t, size_t> find(std::shared_ptr<Neurona> neurona);
    void print();

public:
    std::vector<Capa> capas;

private:
    bool sesgo;
};

#endif
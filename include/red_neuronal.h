#ifndef RED_NEURONAL_H
#define RED_NEURONAL_H

#include <vector>
#include "capa.h"

class RedNeuronal {
public:
    RedNeuronal();
    virtual ~RedNeuronal();
    void Inicializar();
    void Anadir(Capa *capa);
    void Disparar();
    void Propagar();
    void print();

public:
    std::vector<Capa *> capas;
};

#endif
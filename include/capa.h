#ifndef CAPA_H
#define CAPA_H

#include <vector>
#include "neurona.h"

#define PESO_CERO 0
#define PESO_PEQUENO 1

class Capa {
public:
    Capa();
    virtual ~Capa();
    void Inicializar();
    void Anadir(Neurona *neurona);
    void Conectar(Capa *capa, int modo_peso);
    void Conectar(Neurona *neurona, int modo_peso);
    void Disparar();
    void Propagar();

public:
    std::vector<Neurona *> neuronas;
};

#endif
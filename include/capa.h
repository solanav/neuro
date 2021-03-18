#ifndef CAPA_H
#define CAPA_H

#include <vector>
#include "neurona.h"

#define PESO_CERO 0
#define PESO_PEQUENO 1

class Capa {
public:
    Capa();
    Capa(int num_neuronas, float umbral, Neurona::Tipo tipo);
    virtual ~Capa();
    void Inicializar();
    void Anadir(std::shared_ptr<Neurona> neurona);
    void Conectar(Capa *capa, int modo_peso);
    void Conectar(std::shared_ptr<Neurona> neurona, int modo_peso);
    void Disparar();
    void Propagar();
    void print();

public:
    std::vector<std::shared_ptr<Neurona>> neuronas;
};

#endif
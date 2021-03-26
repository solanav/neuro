#ifndef CONEXION_H
#define CONEXION_H

class Conexion;

#include <memory>
#include "neurona.h"

class Conexion {
public:
    Conexion(float peso, std::shared_ptr<Neurona> neurona);
    virtual ~Conexion();
    void Propagar(float valor);
    void print();
public:
    float peso;
    float peso_anterior;
    float valor_recibido;
    std::shared_ptr<Neurona> neurona;
};

#endif
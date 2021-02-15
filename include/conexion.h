#ifndef CONEXION_H
#define CONEXION_H

class Conexion;

#include "neurona.h"

class Conexion {
public:
    Conexion(float peso, Neurona neurona);
    virtual ~Conexion();
    void Propagar(float valor);
public:
    float peso;
    float peso_anterior;
    float valor_recibido;
    Neurona *neurona;
};

#endif
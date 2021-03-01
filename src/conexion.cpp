#include "conexion.h"
#include "neurona.h"

Conexion::Conexion(float peso, Neurona *neurona)
{
    this->peso = peso;
    this->neurona = neurona;
    peso_anterior = 0;
    valor_recibido = 0;
}

Conexion::~Conexion() {}

void Conexion::Propagar(float valor)
{
    valor_recibido = valor;
}

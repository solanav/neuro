#include <iostream>

#include "conexion.h"
#include "neurona.h"

Conexion::Conexion(float peso, std::shared_ptr<Neurona> neurona)
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

void Conexion::print()
{
    std::cout << "\t\t\tCONEXION (" << this << ")" << std::endl;
    std::cout << "\t\t\t\tPeso:           " << peso << std::endl;
    std::cout << "\t\t\t\tPeso Anterior:  " << peso_anterior << std::endl;
    std::cout << "\t\t\t\tNeurona:        " << neurona << std::endl;
}

#include <iostream>

#include "neurona.h"
#include "conexion.h"

Neurona::Neurona(float umbral, Tipo tipo)
{
    this->umbral = umbral;
    this->tipo = tipo;
    conexiones = std::vector<Conexion>();

    if (tipo == Directa) { // TODO
        salida_activa = 1;
        salida_inactiva = 0;
    }
    else if (tipo == Sesgo) {
        salida_activa = 1;
        salida_inactiva = -1;
        sesgo = 1.0;
    }
    else if (tipo == McCulloch) {
        salida_activa = 1;
        salida_inactiva = 0;
    }
    else if (tipo == SigmoideBipolar) {
        salida_activa = 1;
        salida_inactiva = -1;
    }
    else if (tipo == SigmoidePersonalizada) {
        salida_activa = 1;
        salida_inactiva = 0;
    }
    else {
        std::cout << "Eso no existe loco" << std::endl;
    }

    valor = 0;
    f_x = 0;
}

Neurona::Neurona(float umbral, float salida_activa, float salida_inactiva, Tipo tipo)
{
    this->umbral = umbral;
    this->tipo = tipo;
    this->salida_activa = salida_activa;
    this->salida_inactiva = salida_inactiva;

    valor = 0;
    f_x = 0;
}

Neurona::~Neurona() {}

void Neurona::inicializar(float valor)
{
    this->valor = valor;
}

void Neurona::conectar(Neurona *neurona, float peso)
{
    conexiones.push_back(Conexion(peso, neurona));
}

void Neurona::disparar()
{
    if (tipo == Directa)
        f_x = valor;
    else if (tipo == Sesgo)
        f_x = sesgo;
    else if (tipo == McCulloch)
        f_x = valor >= umbral ? salida_activa : salida_inactiva;
    else
        std::cout << "Eso no existe loco" << std::endl;

    for (auto& conexion : conexiones)
        conexion.valor_recibido = f_x;
}

void Neurona::propagar()
{
    for (auto& conexion : conexiones)
        conexion.neurona->valor += conexion.peso * conexion.valor_recibido;
}
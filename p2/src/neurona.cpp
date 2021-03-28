#include <iostream>
#include <memory>
#include <cmath>

#include "neurona.h"
#include "conexion.h"

Neurona::Neurona(float umbral, Tipo tipo)
{
    this->umbral = umbral;
    this->tipo = tipo;
    conexiones = std::vector<Conexion>();

    if (tipo == Directa) {
        salida_activa = 1;
        salida_inactiva = -1;
    }
    else if (tipo == Sesgo) {
        salida_activa = 1;
        salida_inactiva = -1;
    }
    else if (tipo == Perceptron) {
        salida_activa = 1;
        salida_inactiva = -1;
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

void Neurona::conectar(std::shared_ptr<Neurona> neurona, float peso)
{
    conexiones.push_back(Conexion(peso, neurona));
}

void Neurona::disparar()
{
    if (tipo == Directa)
        f_x = valor;
    else if (tipo == McCulloch)
        f_x = valor >= umbral ? salida_activa : salida_inactiva;
    else if (tipo == Perceptron)
    {
        if (valor > umbral)
            f_x = 1;
        else if (valor < -umbral)
            f_x = -1;
        if (valor <= umbral && valor >= -umbral)
            f_x = 0;
    }
    else if (tipo == Sesgo)
        f_x = 1.0;
    else if (tipo == SigmoideBipolar)
        f_x =  2 / (1 + exp(-valor)) - 1;
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

void Neurona::print()
{
    const char *str_tipo;
    if (tipo == Sesgo)
        str_tipo = "Sesgo";
    else if (tipo == Directa)
        str_tipo = "Directa";
    else if (tipo == McCulloch)
        str_tipo = "McCulloch";
    else if (tipo == Perceptron)
        str_tipo = "Perceptron";
    else
        str_tipo = "Otra";

    std::cout << "\tNEURONA " << str_tipo << " (" << this << ")" << std::endl;
    std::cout << "\t\tUmbral:  " << umbral << std::endl;
    std::cout << "\t\tValor:   " << valor << std::endl;
    std::cout << "\t\tF_x:     " << f_x << std::endl;
    for (int i = 0; i < conexiones.size(); i++)
        conexiones[i].print();
}
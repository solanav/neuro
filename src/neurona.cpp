#include <iostream>

#include "neurona.h"
#include "conexion.h"

void Neurona::disparar()
{
    if (tipo == Directa)
        f_x = valor;
    else if (tipo == Sesgo)
        f_x = 1.0;
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
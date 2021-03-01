#include <iostream>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"

int main()
{
    Neurona x1 = Neurona(1, Neurona::Tipo::McCulloch);
    Neurona x2 = Neurona(1, Neurona::Tipo::McCulloch);
    Neurona x3 = Neurona(1, Neurona::Tipo::McCulloch);

    Neurona a12 = Neurona(2, Neurona::Tipo::McCulloch);
    Neurona a23 = Neurona(2, Neurona::Tipo::McCulloch);
    Neurona a13 = Neurona(2, Neurona::Tipo::McCulloch);

    Neurona y = Neurona(1, Neurona::Tipo::McCulloch);

    x1.inicializar(1);
    x2.inicializar(1);
    x3.inicializar(0);

    a12.inicializar(0);
    a23.inicializar(0);
    a13.inicializar(0);

    x1.conectar(&a12, 1);
    x2.conectar(&a12, 1);

    x2.conectar(&a23, 1);
    x3.conectar(&a23, 1);

    x1.conectar(&a13, 1);
    x3.conectar(&a13, 1);

    a12.conectar(&y, 1);
    a23.conectar(&y, 1);
    a13.conectar(&y, 1);

    // Primera capa
    x1.disparar();
    x2.disparar();
    x3.disparar();

    x1.propagar();
    x2.propagar();
    x3.propagar();

    // Segunda capa
    a12.disparar();
    a23.disparar();
    a13.disparar();

    a12.propagar();
    a23.propagar();
    a13.propagar();

    y.disparar();

    std::cout << "y > " << y.f_x << std::endl;

    return 0;
}
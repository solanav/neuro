#include <iostream>
#include <fstream>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"

int main(int argc, char *argv[])
{
    // Capa de entrada
    Neurona x1 = Neurona(1, Neurona::Tipo::McCulloch);
    Neurona x2 = Neurona(1, Neurona::Tipo::McCulloch);
    Neurona x3 = Neurona(1, Neurona::Tipo::McCulloch);
    Capa capa_x = Capa();
    capa_x.Anadir(&x1);
    capa_x.Anadir(&x2);
    capa_x.Anadir(&x3);

    // Capa intermedia
    Neurona a12 = Neurona(2, Neurona::Tipo::McCulloch);
    Neurona a23 = Neurona(2, Neurona::Tipo::McCulloch);
    Neurona a13 = Neurona(2, Neurona::Tipo::McCulloch);
    Capa capa_a = Capa();
    capa_a.Anadir(&a12);
    capa_a.Anadir(&a23);
    capa_a.Anadir(&a13);

    // Capa de salida
    Neurona y = Neurona(1, Neurona::Tipo::McCulloch);
    Capa capa_y = Capa();
    capa_y.Anadir(&y);

    // Creamos la red neuronal
    RedNeuronal red = RedNeuronal();
    red.Anadir(&capa_x);
    red.Anadir(&capa_a);
    red.Anadir(&capa_y);

    // Conectamos las neuronas
    x1.conectar(&a12, 1);
    x2.conectar(&a12, 1);
    x2.conectar(&a23, 1);
    x3.conectar(&a23, 1);
    x1.conectar(&a13, 1);
    x3.conectar(&a13, 1);
    a12.conectar(&y, 1);
    a23.conectar(&y, 1);
    a13.conectar(&y, 1);

    std::ifstream infile("entradas.txt");
    std::ofstream output;
    output.open("results_mp.txt");
    float a, b, c;

    output << "x1\tx2\tx3\ta12\ta23\ta13\ty" << std::endl;
    while (infile >> a >> b >> c)
    {
        x1.inicializar(a);
        x2.inicializar(b);
        x3.inicializar(c);

        red.Disparar();
        red.Inicializar();
        red.Propagar();

        output << x1.f_x << "\t" << x2.f_x << "\t" << x3.f_x << "\t";
        output << a12.f_x << "\t" << a23.f_x << "\t" << a13.f_x << "\t";
        output << y.f_x << std::endl;
    }

    for (int i = 0; i < red.capas.size() - 1; i++)
    {
        red.Disparar();
        red.Inicializar();
        red.Propagar();
        output << "-\t-\t-\t";
        output << a12.f_x << "\t" << a23.f_x << "\t" << a13.f_x << "\t";
        output << y.f_x << std::endl;
    }

    return 0;
}
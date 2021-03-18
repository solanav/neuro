#include <iostream>
#include <fstream>
#include <map>

#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"

int main(int argc, char *argv[])
{
    std::vector<std::tuple<size_t, Neurona::Tipo>> neurona_descriptor {
        {3, Neurona::Tipo::McCulloch},
        {3, Neurona::Tipo::McCulloch},
        {1, Neurona::Tipo::McCulloch},
    };

    RedNeuronal red_test = RedNeuronal(1, neurona_descriptor);

    float peso = 1;

    // Conectamos las neuronas
    red_test.conectar(0, 0, 1, 0, peso);
    red_test.conectar(0, 0, 1, 2, peso);
    red_test.conectar(0, 1, 1, 0, peso);
    red_test.conectar(0, 1, 1, 1, peso);
    red_test.conectar(0, 2, 1, 1, peso);
    red_test.conectar(0, 2, 1, 2, peso);
    red_test.conectar(1, 0, 2, 0, peso);
    red_test.conectar(1, 0, 2, 0, peso);
    red_test.conectar(1, 0, 2, 0, peso);

    red_test.print();

    return 1;

    // Capa de entrada
    auto x1 = std::make_shared<Neurona>(1, Neurona::Tipo::McCulloch);
    auto x2 = std::make_shared<Neurona>(1, Neurona::Tipo::McCulloch);
    auto x3 = std::make_shared<Neurona>(1, Neurona::Tipo::McCulloch);
    Capa capa_x = Capa();
    capa_x.Anadir(x1);
    capa_x.Anadir(x2);
    capa_x.Anadir(x3);

    // Capa intermedia
    auto a12 = std::make_shared<Neurona>(2, Neurona::Tipo::McCulloch);
    auto a23 = std::make_shared<Neurona>(2, Neurona::Tipo::McCulloch);
    auto a13 = std::make_shared<Neurona>(2, Neurona::Tipo::McCulloch);
    Capa capa_a = Capa();

    // Capa de salida
    auto y = std::make_shared<Neurona>(1, Neurona::Tipo::McCulloch);
    Capa capa_y = Capa();
    capa_y.Anadir(y);

    // Creamos la red neuronal
    RedNeuronal red = RedNeuronal();
    red.Anadir(capa_x);
    red.Anadir(capa_a);
    red.Anadir(capa_y);

    // Conectamos las neuronas
    x1->conectar(a12, 1);
    x2->conectar(a12, 1);
    x2->conectar(a23, 1);
    x3->conectar(a23, 1);
    x1->conectar(a13, 1);
    x3->conectar(a13, 1);
    a12->conectar(y, 1);
    a23->conectar(y, 1);
    a13->conectar(y, 1);

    std::ifstream infile("inputs/entradas.txt");
    std::ofstream output;
    output.open("results_mp.txt");
    float a, b, c;

    output << "x1\tx2\tx3\ta12\ta23\ta13\ty" << std::endl;
    while (infile >> a >> b >> c)
    {
        x1->inicializar(a);
        x2->inicializar(b);
        x3->inicializar(c);

        red.Disparar();
        red.Inicializar();
        red.Propagar();

        output << x1->f_x << "\t" << x2->f_x << "\t" << x3->f_x << "\t";
        output << a12->f_x << "\t" << a23->f_x << "\t" << a13->f_x << "\t";
        output << y->f_x << std::endl;
    }

    for (int i = 0; i < red.capas.size() - 1; i++)
    {
        red.Disparar();
        red.Inicializar();
        red.Propagar();

        output << "-\t-\t-\t";
        output << a12->f_x << "\t" << a23->f_x << "\t" << a13->f_x << "\t";
        output << y->f_x << std::endl;
    }

    return 0;
}
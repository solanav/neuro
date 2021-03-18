#include <iostream>
#include <fstream>
#include <map>

#include "red_neuronal.h"

RedNeuronal::RedNeuronal()
{
    capas = std::vector<Capa>();
}

RedNeuronal::RedNeuronal(float umbral, std::vector<std::tuple<size_t, Neurona::Tipo>> neuronas)
{
    capas = std::vector<Capa>();

    size_t num_capas = neuronas.size();
    for (size_t i = 0; i < num_capas; i++)
    {
        auto [num_neuronas, tipo] = neuronas[i];
        Capa tmp_capa = Capa(num_neuronas, umbral, tipo);

        capas.push_back(tmp_capa);
    }
}

RedNeuronal::~RedNeuronal() {}

void RedNeuronal::Inicializar()
{
    for (auto& capa : capas)
        capa.Inicializar();
}

void RedNeuronal::Anadir(Capa capa)
{
    capas.push_back(capa);
}

void RedNeuronal::Disparar()
{
    for (auto& capa : capas)
        capa.Disparar();
}

void RedNeuronal::Propagar()
{
    for (auto& capa : capas)
        capa.Propagar();
}

void RedNeuronal::conectar(int capa_x, int neurona_x, int capa_y, int neurona_y, float peso)
{
    std::cout << capa_x << "; " << neurona_x << "; " << capa_y << "; " << neurona_y << std::endl;

    size_t num_capas = capas.size();
    if (capa_x >= num_capas || capa_y >= num_capas)
        std::cout << "Indice de la capa erroneo" << std::endl;

    size_t capax_size = capas[capa_x].neuronas.size();
    size_t capay_size = capas[capa_y].neuronas.size();
    if (neurona_x >= capax_size || neurona_y >= capay_size)
        std::cout << "Indice de las neuronas erroneo" << std::endl;

    auto nx = capas[capa_x].neuronas[neurona_x];
    auto ny = capas[capa_y].neuronas[neurona_y];

    nx->conectar(ny, peso);
}

void RedNeuronal::print()
{
    std::cout << "==========================================================" << std::endl;
    for (int i = 0; i < capas.size(); i++)
        capas[i].print();

}

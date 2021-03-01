#include "red_neuronal.h"

RedNeuronal::RedNeuronal()
{
    capas = std::vector<Capa *>();
}

RedNeuronal::~RedNeuronal() {}

void RedNeuronal::Inicializar()
{
    for (auto& capa : capas)
        capa->Inicializar();
}

void RedNeuronal::Anadir(Capa *capa)
{
    capas.push_back(capa);
}

void RedNeuronal::Disparar()
{
    for (auto& capa : capas)
        capa->Disparar();
}

void RedNeuronal::Propagar()
{
    for (auto& capa : capas)
        capa->Propagar();
}


#include "capa.h"

Capa::Capa()
{
    neuronas = std::vector<Neurona *>();
}

Capa::~Capa() {}

void Capa::Inicializar() {
    for (auto& neurona : neuronas)
        neurona->valor = 0;
}

void Capa::Anadir(Neurona *neurona)
{
    neuronas.push_back(neurona);
}

void Capa::Conectar(Capa *capa, int modo_peso)
{

}

void Capa::Conectar(Neurona *neurona, int modo_peso)
{

}

void Capa::Disparar()
{
    for (auto& neurona : neuronas)
        neurona->disparar();
}

void Capa::Propagar()
{
    for (auto& neurona : neuronas)
        neurona->propagar();
}

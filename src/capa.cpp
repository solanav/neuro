#include <iostream>

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
    for (auto& neurona : capa->neuronas)
        Conectar(neurona, modo_peso);
}

void Capa::Conectar(Neurona *neurona, int modo_peso)
{
    
    if (modo_peso == PESO_CERO)
        for (auto& self_neurona : this->neuronas)
            self_neurona->conectar(neurona, 0);

    else if (modo_peso == PESO_PEQUENO)
        for (auto& self_neurona : this->neuronas)
            self_neurona->conectar(neurona, 0.1 + (float(rand()) / (float(RAND_MAX) + 0.5)));

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

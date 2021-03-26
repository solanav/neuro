#include <iostream>

#include "capa.h"

Capa::Capa()
{
    neuronas = std::vector<std::shared_ptr<Neurona>>();
}

Capa::Capa(int num_neuronas, float umbral, Neurona::Tipo tipo)
{
    neuronas = std::vector<std::shared_ptr<Neurona>>();

    for (int i = 0; i < num_neuronas; i++)
    {
        auto tmp_neurona = std::make_shared<Neurona>(umbral, Neurona::Tipo::McCulloch);
        neuronas.push_back(tmp_neurona);
    }
}

Capa::~Capa() {}

void Capa::Inicializar() {
    for (auto& neurona : neuronas)
        neurona->inicializar(0);
}

void Capa::Anadir(std::shared_ptr<Neurona> neurona)
{
    neuronas.push_back(neurona);
}

void Capa::Conectar(Capa *capa, int modo_peso)
{
    for (auto& neurona : capa->neuronas)
        Conectar(neurona, modo_peso);
}

void Capa::Conectar(std::shared_ptr<Neurona> neurona, int modo_peso)
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

size_t Capa::find(std::shared_ptr<Neurona> neurona)
{
    for (size_t i = 0; i < neuronas.size(); i++)
    {
        if (neuronas[i] == neurona)
            return i;
    }

    return -1;
}

void Capa::print()
{
    std::cout << "CAPA (" << this << ")" << std::endl;
    for (int i = 0; i < neuronas.size(); i++)
        neuronas[i]->print();
}

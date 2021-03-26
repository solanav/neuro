#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "red_neuronal.h"

RedNeuronal::RedNeuronal()
{
    capas = std::vector<Capa>();
}

RedNeuronal::RedNeuronal(std::vector<std::tuple<float, size_t, Neurona::Tipo>> descriptor, bool sesgo)
{
    capas = std::vector<Capa>();
    this->sesgo = sesgo;
    size_t num_capas = descriptor.size();
    for (size_t i = 0; i < num_capas; i++)
    {
        auto [umbral, num_neuronas, tipo] = descriptor[i];
        Capa tmp_capa = Capa(num_neuronas, umbral, tipo);

        // Si se nos pide meter sesgo, metemos una neurona de tipo sesgo
        // en todas las capas excepto la ultima.
        if (sesgo && i < num_capas - 1)
            tmp_capa.Anadir(std::make_shared<Neurona>(umbral, Neurona::Tipo::Sesgo));

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

void RedNeuronal::step(std::vector<float> inputs)
{
    int sesgo_add = sesgo ? 1 : 0;
    auto capa_entrada = capas[0];
    if (capa_entrada.neuronas.size() != inputs.size() + sesgo)
    {
        std::cout
            << capa_entrada.neuronas.size() << " neuronas pero "
            << inputs.size() + sesgo << " inputs. Please fix."
            << std::endl;

        exit(-1);
    }

    for (int i = 0; i < inputs.size(); i++)
        capa_entrada.neuronas[i]->inicializar(inputs[i]);

    Disparar();
    Inicializar();
    Propagar();
}

void RedNeuronal::next(std::vector<float> inputs)
{
    step(inputs);

    size_t num_capas = capas.size();
    for (size_t i = 0; i < num_capas - 1; i++)
        step(inputs);
}

void RedNeuronal::conectar(int modo_peso)
{
    size_t num_capas = capas.size();
    for (size_t i = 0; i < num_capas - 1; i++)
    {
        capas[i].Conectar(&(capas[i + 1]), modo_peso);
    }
}

void RedNeuronal::conectar(int capa_x, int neurona_x, int capa_y, int neurona_y, float peso)
{
    size_t num_capas = capas.size();
    if (capa_x >= num_capas || capa_y >= num_capas)
    {
        std::cout << capa_x << "; " << neurona_x << "; " << capa_y << "; " << neurona_y << std::endl;
        std::cout << "Indice de la capa erroneo" << std::endl;
    }

    size_t capax_size = capas[capa_x].neuronas.size();
    size_t capay_size = capas[capa_y].neuronas.size();
    if (neurona_x >= capax_size || neurona_y >= capay_size)
    {
        std::cout << capa_x << "; " << neurona_x << "; " << capa_y << "; " << neurona_y << std::endl;
        std::cout << "Indice de las neuronas erroneo" << std::endl;
    }

    auto nx = capas[capa_x].neuronas[neurona_x];
    auto ny = capas[capa_y].neuronas[neurona_y];

    nx->conectar(ny, peso);
}

std::tuple<size_t, size_t> RedNeuronal::find(std::shared_ptr<Neurona> neurona)
{
    for (size_t i = 0; i < capas.size(); i++)
    {
        size_t ii = capas[i].find(neurona);
        if (ii != -1)
            return std::tuple<size_t, size_t>(i, ii);
    }

    return std::tuple<size_t, size_t>(-1, -1);
}

void RedNeuronal::print_dot(std::string file_name)
{
    std::ostringstream start;
    std::ostringstream middle;
    std::ostringstream end;

    start << "digraph graphname {" << "\n";
    start << "\trankdir=\"LR\";" << "\n";

    // Por cada capa
    for (size_t capa_i = 0; capa_i < capas.size(); capa_i++)
    {
        middle << "\tsubgraph cluster_" << capa_i << " {\n";
        middle << "\t\tnode [style=filled];\n";

        // Por cada neurona en la capa
        for (size_t neurona_i = 0; neurona_i < capas[capa_i].neuronas.size(); neurona_i++)
        {
            auto curr_neurona = capas[capa_i].neuronas[neurona_i];
            std::string curr_neurona_name = "n"
                + std::to_string(capa_i)
                + std::to_string(neurona_i)
                + " [" + std::to_string(curr_neurona->f_x) + "]";

            // Si estamos en la capa de entrada
            if (capa_i == 0)
            {
                end << "\t\"void_" << curr_neurona_name << "\" [style=invis,fixedsize=true,width=0];\n";
                end << "\t\"void_" << curr_neurona_name << "\" -> \"" << curr_neurona_name
                    << "\" [label=" << curr_neurona->valor << "];\n";
            }

            // Si estamos en la capa de salida
            else if (capa_i == capas.size() - 1)
            {
                end << "\t\"void_" << curr_neurona_name << "\" [style=invis,fixedsize=true,width=0];\n";
                end << "\t\t\"" << curr_neurona_name << "\" -> \"void_" << curr_neurona_name
                    << "\" [label=" << curr_neurona->f_x << "];\n";

            }

            middle << "\t\t\"" << curr_neurona_name << "\";\n";

            // Conexiones
            for (size_t con_i = 0; con_i < curr_neurona->conexiones.size(); con_i++)
            {
                auto next_neurona = curr_neurona->conexiones[con_i].neurona;
                auto [next_capa_i, next_neurona_i] = find(next_neurona);
                std::string next_neurona_name = "n"
                    + std::to_string(next_capa_i)
                    + std::to_string(next_neurona_i)
                    + " [" + std::to_string(next_neurona->f_x) + "]";

                end << "\t\"" << curr_neurona_name << "\" -> \"" << next_neurona_name
                    << "\" [label=" << curr_neurona->conexiones[con_i].peso << "];\n";
            }
        }

        middle << "\t\tlabel = \"capa" << capa_i << "\";\n";
        middle << "\t}\n";
    }

    end << "}";

    std::string start_s = start.str();
    std::string middle_s = middle.str();
    std::string end_s = end.str();

    // Write to file
    std::ofstream output;
    output.open(file_name);

    output << start_s << middle_s << end_s;

    output.close();
}

void RedNeuronal::print()
{
    std::cout << "==========================================================" << std::endl;
    for (int i = 0; i < capas.size(); i++)
        capas[i].print();

}

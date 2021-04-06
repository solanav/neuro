#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include <iomanip>

#include "../include/mates.h"

std::vector<float> dot_product(std::vector<float> x, std::vector<std::vector<float>> y)
{
    std::vector<float> res;

    for (int i = 0; i < y.size(); i++)
    {
        float tmp = 0;

        for (int j = 0; j < y[i].size(); j++)
            tmp += x[j] * y[i][j];

        res.push_back(tmp);
    }

    return res;
}

std::vector<std::vector<float>> add_tensors(std::vector<std::vector<float>> x, std::vector<std::vector<float>> y)
{
    // Comprobaciones
    if (x.size() != y.size())
    {
        std::cout << "Tensors are not the same size, cannot add them" << std::endl;
        exit(0);
    }
    
    std::vector<std::vector<float>> res;

    for (int i = 0; i < x.size(); i++)
        res.push_back(add_tensors(x[i], y[i]));

    return res;
}

std::vector<float> add_tensors(std::vector<float> x, std::vector<float> y)
{
    // Comprobaciones
    if (x.size() != y.size())
    {
        std::cout << "Tensors are not the same size, cannot add them" << std::endl;
        exit(0);
    }

    std::vector<float> res(y.size());
    for (int i = 0; i < y.size(); i++)
        res[i] = x[i] + y[i];

    return res;
}

std::vector<float> sub_tensors(std::vector<float> x, std::vector<float> y)
{
    // Comprobaciones
    if (x.size() != y.size())
    {
        std::cout << "Tensors are not the same size, cannot substract them" << std::endl;
        exit(0);
    }

    std::vector<float> res;
    for (int i = 0; i < x.size(); i++)
        res.push_back(x[i] - y[i]);

    return res;
}

float random_number(float min, float max)
{
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);

    std::uniform_real_distribution<float> urd(min, max);

    return urd(eng);
}

void print_tensor(std::vector<float> tensor)
{
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    std::cout << "| ";
    for (int i = 0; i < tensor.size(); i++)
    {
        if (tensor[i] < 0)
            std::cout << tensor[i] << "| ";
        else
            std::cout << tensor[i] << " | ";
    }
    std::cout << "\n" << std::endl;
}

float sigmoide_binaria(float value)
{
    return 1 / (1 + exp(0 - value));
}

float sigmoide_binaria_der(float value)
{
    return sigmoide_binaria(value) * (1 - sigmoide_binaria(value));
}

float sigmoide_bipolar(float value)
{
    return (2 / (1 + exp(0 - value))) - 1;
}

float sigmoide_bipolar_der(float value)
{
    return 0.5 * (1 + sigmoide_bipolar(value)) * (1 - sigmoide_bipolar(value));
}

std::vector<float> sigmoide_bipolar(std::vector<float> value)
{
    std::vector<float> res;
    for (int i = 0; i < value.size(); i++)
        res.push_back(sigmoide_bipolar(value[i]));
    return res;
}

std::vector<float> sigmoide_binaria(std::vector<float> value)
{
    std::vector<float> res;
    for (int i = 0; i < value.size(); i++)
        res.push_back(sigmoide_binaria(value[i]));
    return res;
}

std::vector<float> sigmoide(std::vector<float> value, int bi)
{
    if (bi == 0)
        return sigmoide_bipolar(value);
    else
        return sigmoide_binaria(value);
}

float sigmoide_der(float value, int bi)
{
    if (bi == 0)
        return sigmoide_bipolar_der(value);
    else
        return sigmoide_binaria_der(value);
}

void print_tensor(std::vector<std::vector<float>> tensor)
{
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    for (int i = 0; i < tensor.size(); i++)
    {
        std::cout << "| ";
        for (int j = 0; j < tensor[i].size(); j++)
        {
            if (tensor[i][j] < 0)
                std::cout << tensor[i][j] << "| ";
            else
                std::cout << tensor[i][j] << " | ";

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

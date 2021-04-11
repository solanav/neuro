#ifndef MATES_H
#define MATES_H

// Operaciones entre tensores
std::vector<float> dot_product(std::vector<float> x, std::vector<std::vector<float>> y);

std::vector<float> add_tensors(std::vector<float> x, std::vector<float> y);
std::vector<std::vector<float>> add_tensors(std::vector<std::vector<float>> x, std::vector<std::vector<float>> y);
std::vector<float> sub_tensors(std::vector<float> x, std::vector<float> y);

std::vector<float> average_tensors(std::vector<std::vector<float>> tensors);
std::vector<std::vector<float>> average_tensors(std::vector<std::vector<std::vector<float>>> tensors);

// Funciones logisticas, etc.
std::vector<float> sigmoide(std::vector<float> value, int bi);
float sigmoide_der(float value, int bi);

// Utils
float random_number(float min, float max);

// Prints
void print_tensor(std::vector<float> tensor);
void print_tensor(std::vector<std::vector<float>> tensor);

#endif
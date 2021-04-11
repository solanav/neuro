#ifndef LECTOR_H
#define LECTOR_H

#include <vector>
#include <string>

class Lector {
public:
    Lector();
    ~Lector();
    void leer1(const char *fichero, float por);
    void leer2(const char *fichero);
    void leer3(const char *fichero_entreno, const char *fichero_test);
    void normalize();
private:
    void leer(const char *fichero);

public:
    std::vector<std::vector<float>> entradas_entrenamiento;
    std::vector<std::vector<float>> entradas_test;
    std::vector<std::vector<float>> salidas_entrenamiento;
    std::vector<std::vector<float>> salidas_test;
    int num_entradas;
    int num_salidas;
private:
    std::vector<std::string> data;
};

#endif
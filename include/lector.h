#ifndef LECTOR_H
#define LECTOR_H

#include <vector>
#include <string>

class Lector {
public:
    Lector();
    ~Lector();
    void leer1(char *fichero, float por);
    void leer2(char *fichero);
    void leer3(char *fichero_entreno, char *fichero_test);
private:
    void leer(char *fichero);

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
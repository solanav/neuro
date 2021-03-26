#ifndef NEURONA_H
#define NEURONA_H

class Neurona;

#include <vector>
#include "conexion.h"

class Neurona {
public:
    enum Tipo {
        Directa,
        McCulloch,
        Sesgo,
        SigmoideBipolar,
        SigmoidePersonalizada,
        Perceptron
    };
    Neurona(float umbral, Tipo tipo);
    Neurona(float umbral, float salida_activa, float salida_inactiva, Tipo tipo);
    virtual ~Neurona();
    void inicializar(float valor);
    void conectar(std::shared_ptr<Neurona> neurona, float peso);
    void disparar();
    void propagar();
    void print();

public:
    float umbral;
    float valor;
    float salida_activa;
    float salida_inactiva;
    Tipo tipo;
    float f_x;
    std::vector<Conexion> conexiones;
};

#endif
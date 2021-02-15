#ifndef NEURONA_H
#define NEURONA_H

class Neurona;

#include <vector>
#include "conexion.h"

class Neurona {
public:
    enum {
        Directa,
        McCulloch,
        Sesgo,
        SigmoideBipolar,
        SigmoidePersonalizada
    };
    Neurona(float umbral, int tipo);
    Neurona(float umbral, float salida_activa, float salida_inactiva, int tipo);
    virtual ~Neurona();
    void inicializar(float valor);
    void conectar(Neurona *neurona, float peso);
    void disparar();
    void propagar();

public:
    float umbral;
    float valor;
    float salida_activa;
    float salida_inactiva;
    int tipo;
    float f_x;
    std::vector<Conexion> conexiones;
};

#endif
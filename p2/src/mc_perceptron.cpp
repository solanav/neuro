#include "neurona.h"
#include "conexion.h"
#include "capa.h"
#include "red_neuronal.h"
#include "lector.h"

int main(int argc, char const *argv[])
{
    std::vector<std::tuple<float, size_t, Neurona::Tipo>> descriptor {
        {0.2, 2, Neurona::Directa},
        {0.2, 2, Neurona::SigmoideBipolar},
        {0.2, 1, Neurona::SigmoideBipolar},//UwU
    };
    
    RedNeuronal red = RedNeuronal(descriptor, true);
    return 0;
}

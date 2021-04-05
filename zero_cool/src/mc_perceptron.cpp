#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#include "red_neuronal.h"
#include "lector.h"
#include "mates.h"

#define BIPOLAR 0
#define BINARIA 1

#define MAX_EPOCAS 500

int main(int argc, char const *argv[])
{
    Lector l = Lector();
    l.leer2((char *)"inputs/problema_real1.txt");

    for (float tasa_ap = 0.01; tasa_ap < 0.5; tasa_ap += 0.02)
    {
        for (int num_capas = 2; num_capas < 8; num_capas++)
        {
            RedNeuronal red = RedNeuronal(num_capas, tasa_ap, BINARIA, l, "output.csv", MAX_EPOCAS);

            red.train();
            red.test();
        }
    }

    return 0;
}

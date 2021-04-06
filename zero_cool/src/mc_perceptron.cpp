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

#define MAX_EPOCAS 500000

void test_and()
{
    Lector l = Lector();
    l.leer2((char *)"inputs/and.txt");

    RedNeuronal red(2, 0.01, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_xor()
{
    Lector l = Lector();
    l.leer2((char *)"inputs/xor.txt");

    RedNeuronal red(4, 0.02, BINARIA, l, "/dev/null", 500000);
    red.train();
    red.test();
}

void test_or()
{
    Lector l = Lector();
    l.leer2((char *)"inputs/or.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_nand()
{
    Lector l = Lector();
    l.leer2((char *)"inputs/nand.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

int main(int argc, char const *argv[])
{
    Lector l = Lector();
    l.leer2((char *)"inputs/nand.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "output.csv", 5000);
    red.train();
    red.test();

    return 0;
}

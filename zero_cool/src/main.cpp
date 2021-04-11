#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <thread>

#include "red_neuronal.h"
#include "lector.h"
#include "mates.h"

#define MAX_EPOCAS 500000

void test_and()
{
    Lector l = Lector();
    l.leer2((char *)"data/and.txt");

    RedNeuronal red(2, 0.01, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_xor()
{
    Lector l = Lector();
    l.leer2((char *)"data/xor.txt");

    RedNeuronal red(4, 0.02, BINARIA, l, "/dev/null", 500000);
    red.train();
    red.test();
}

void test_or()
{
    Lector l = Lector();
    l.leer2((char *)"data/or.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_nand()
{
    Lector l = Lector();
    l.leer2((char *)"data/nand.txt");

    RedNeuronal red(4, 0.02, BIPOLAR, l, "/dev/null", 5000);
    red.train();
    red.test();
}

void test_problema_real1()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real1.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 1000);
    red.train2();
    red.test();
    std::cout << "problema_real1" << std::endl;
}

void test_problema_real2()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real2.txt");

    RedNeuronal red(2, 0.4, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real2" << std::endl;
}

void test_problema_real3()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real3.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real3" << std::endl;
}

void test_problema_real4()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real4.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real4" << std::endl;
}

void test_problema_real5()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real5.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real5" << std::endl;
}

void test_problema_real6()
{
    Lector l = Lector();
    l.leer2((char *)"data/problema_real6.txt");

    RedNeuronal red(4, 0.1, BIPOLAR, l, "/dev/null", 10000);
    red.train2();
    red.test();
    std::cout << "problema_real6" << std::endl;
}

int main(int argc, char const *argv[])
{
    test_problema_real2();
    return 0;
}

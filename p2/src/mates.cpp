#include <cmath>

float sigmoide_bipolar_der(float f_x) {
    return 0.5 * (1 + f_x) * (1 - f_x);
}



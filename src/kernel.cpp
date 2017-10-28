#include "kernel.h"


Kernel::Kernel(int size, int divisor, std::vector<int> coefficients) {
    this->size = size;
    this->divisor = divisor;
    this->coefficients = coefficients;
}

int Kernel::getSize() const {
    return size;
}

int Kernel::getDivisor() const {
    return divisor;
}

const std::vector<int> &Kernel::getCoefficients() const {
    return coefficients;
}




#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H


#include <vector>

class Kernel {

public:
    Kernel(int size, int divisor, std::vector<int> coefficients);

    int getSize() const;

    int getDivisor() const;

    const std::vector<int> &getCoefficients() const;

private:
    int size;
    int divisor;
    std::vector<int> coefficients;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H

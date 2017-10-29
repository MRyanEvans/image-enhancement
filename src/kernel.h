

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H


#include <vector>

/**
 * A wrapper for a simple kernel convolution.
 */
class Kernel {

public:
    /**
     *
     * @param size The side length of the kernel.  For a 'n x n', this would be 'n'.
     * @param divisor The value to divide the kernel by.
     * @param coefficients The values to use in kernel convolution.
     */
    Kernel(int size, int divisor, std::vector<int> coefficients);

    int getSize() const;

    int getDivisor() const;

    const std::vector<int> &getCoefficients() const;

    int getCoefficient(int x, int y);

private:
    int size;
    int divisor;
    std::vector<int> coefficients;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNEL_H

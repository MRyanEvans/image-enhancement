#include "MeanFilter.h"
#include "../kernel.h"
#include "../KernelImageConvolver.h"

std::unique_ptr<cv::Mat> MeanFilter::applyFilter() {

    std::vector<int> coefficients{1, 1, 1,
                                  1, 1, 1,
                                  1, 1, 1
    };
    Kernel kernel(3, 9, coefficients);
    KernelImageConvolver kernelImageConvolver;
    return kernelImageConvolver.convolveKernelAndImage(kernel, this->sourceImage);
}
#include "LowPassSpatialFilter.h"
#include "../kernel.h"
#include "../KernelImageConvolver.h"

/**
 * Applies a low pass (averaging) kernel to an image.
 * @return The averaged image.
 */
std::unique_ptr<cv::Mat> LowPassSpatialFilter::applyFilter() {
    std::vector<int> coefficients{1, 1, 1,
                                  1, 1, 1,
                                  1, 1, 1
    };
    Kernel kernel(3, 9, coefficients);
    KernelImageConvolver kernelImageConvolver;
    return kernelImageConvolver.convolveKernelAndImage(kernel, this->sourceImage);
}
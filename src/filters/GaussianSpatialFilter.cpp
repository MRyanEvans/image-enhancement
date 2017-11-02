

#include "GaussianSpatialFilter.h"
#include "../KernelImageConvolver.h"
/**
 * Applies the standard Gaussian kernel to an image.
 * @return The filtered image.
 */
std::unique_ptr<cv::Mat> GaussianSpatialFilter::applyFilter() {
    // Gaussian kernel is a 5x5 kernel with factor 1/273 with following coefficients:
    std::vector<int> coefficients{1, 4, 7, 4, 1,
                                  4, 16, 26, 16, 4,
                                  7, 26, 41, 26, 7,
                                  4, 16, 26, 16, 4,
                                  1, 4, 7, 4, 1
    };
    Kernel kernel(5, 273, coefficients);
    KernelImageConvolver kernelImageConvolver;
    return kernelImageConvolver.convolveKernelAndImage(kernel, this->sourceImage);
}

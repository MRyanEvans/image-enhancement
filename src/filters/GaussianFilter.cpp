

#include "GaussianFilter.h"
#include "../KernelImageConvolver.h"

std::unique_ptr<cv::Mat> GaussianFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );


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
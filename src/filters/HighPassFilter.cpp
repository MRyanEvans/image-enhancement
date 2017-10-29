#include "HighPassFilter.h"
#include "../KernelImageConvolver.h"

std::unique_ptr<cv::Mat> HighPassFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );

    std::vector<int> coefficients{-1, -1, -1,
                                  -1, 8, -1,
                                  -1, -1, -1
    };
    Kernel kernel(3, 9, coefficients);
    KernelImageConvolver kernelImageConvolver;
    return kernelImageConvolver.convolveKernelAndImage(kernel, this->sourceImage);
}


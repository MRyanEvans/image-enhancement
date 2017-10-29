

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H


#include <bits/unique_ptr.h>
#include <opencv2/core/mat.hpp>
#include <memory>
#include "kernel.h"

class KernelImageConvolver {

public:
    std::unique_ptr<cv::Mat> convolveKernelAndImage(Kernel kernel, std::shared_ptr<cv::Mat> image);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H

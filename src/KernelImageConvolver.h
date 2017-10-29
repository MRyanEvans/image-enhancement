

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H


#include <opencv2/core/mat.hpp>
#include <memory>
#include "kernel.h"

/**
 * Applies a kernel to a given image.
 */
class KernelImageConvolver {

public:
    std::unique_ptr<cv::Mat> convolveKernelAndImage(Kernel kernel, std::shared_ptr<cv::Mat> image);

    std::vector<int> convolveKernelOverNeighbourhood(std::shared_ptr<cv::Mat> image, Kernel kernel, int x, int y,
                                                     int offset);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_KERNELIMAGECONVOLVER_H

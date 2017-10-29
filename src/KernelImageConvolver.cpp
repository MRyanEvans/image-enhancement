

#include <numeric>
#include "KernelImageConvolver.h"

/**
 * Applies a given kernel to a given image.
 * @param kernel The filter function.
 * @param image The image to apply the kernel to.
 * @return An image with the applied kernel.
 */
std::unique_ptr<cv::Mat> KernelImageConvolver::convolveKernelAndImage(Kernel kernel, std::shared_ptr<cv::Mat> image) {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            image.get()->rows,
            image.get()->cols,
            image.get()->type()
    );
    //TODO modularise this

    // The number of pixels to 'ignore' on each side to allow full neighbourhoods.
    // For example, a 3 x 3 kernel should be offset by one pixel.
    int offset = (kernel.getSize() - 1) / 2;
    for (int x = offset; x < image->cols - offset; x++) {
        for (int y = offset; y < image->rows - offset; y++) {
            std::vector<int> values;
            // Apply kernel to neighbourhood.
            values= convolveKernelOverNeighbourhood(image, kernel, x, y, offset);
            // Determine sum of convolved values.
            int sum = std::accumulate(values.begin(), values.end(), 0);

            ( outputImage.get())->at<uchar>(y, x) = sum;
        }

    }
    return outputImage;
}

/**
 * Apply a given kernel to an image pixel's neighbourhood.
 * @param image The image to read.
 * @param kernel The kernel to apply.
 * @param x The center pixel of the neighbourhood.
 * @param y The center pixel of the neighbourhood.
 * @param offset The kernel index offset.
 * @return The values of the convolved neighbourhood.
 */
std::vector<int> KernelImageConvolver::convolveKernelOverNeighbourhood(std::shared_ptr<cv::Mat> image, Kernel kernel,
                                                                       int x, int y, int offset){
    std::vector<int> values;
    // Go over each kernel item
    for (int dx = 0; dx < kernel.getSize(); dx++) {
        for (int dy = 0; dy < kernel.getSize(); dy++) {
            int kernelCoefficient = kernel.getCoefficient(dx, dy);

            //Determine the absolute location of the neighbourhood pixel and read its value.
            int pixelX = x + (dx - offset);
            int pixelY = y + (dy - offset);
            auto pixelValue = static_cast<int>(image->at<uchar>(pixelY, pixelX));

            // Apply the kernel function to the pixel.
            float value = (float) (kernelCoefficient * pixelValue) / (float) kernel.getDivisor();
            values.push_back((int) value);
        }
    }
    return values;
}
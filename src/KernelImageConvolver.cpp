

#include "KernelImageConvolver.h"

std::unique_ptr<cv::Mat> KernelImageConvolver::convolveKernelAndImage(Kernel kernel, std::shared_ptr<cv::Mat> image) {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            image.get()->rows,
            image.get()->cols,
            image.get()->type()
    );
    //TODO modularise this

    int offset = (kernel.getSize() - 1) / 2;
    for (int x = offset; x < image->cols - offset; x++) {
        for (int y = offset; y < image->rows - offset; y++) {
            std::vector<int> values;
            for (int dx = 0; dx < kernel.getSize(); dx++) {
                for (int dy = 0; dy < kernel.getSize(); dy++) {
                    int kernelCoefficient = kernel.getCoefficient(dx, dy);
                    int pixelX = x + (dx - offset);
                    int pixelY = y + (dy - offset);
                    auto pixelValue = static_cast<int>(image->at<uchar>(pixelY, pixelX));

                    float value = (float) (kernelCoefficient * pixelValue) / (float) kernel.getDivisor();
                    values.push_back((int) value);
                }
            }
            int sum = 0;
            for(int i = 0; i < values.size(); i++) {
                sum += values.at(i);
            }
            ( outputImage.get())->at<uchar>(y, x) = sum;
        }

    }
    return outputImage;
}

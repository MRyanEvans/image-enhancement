#include "MedianFilter.h"

std::unique_ptr<cv::Mat> MedianFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );

    return outputImage;
}

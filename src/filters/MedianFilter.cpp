#include "MedianFilter.h"

std::unique_ptr<cv::Mat> MedianFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );

    int numRows = this->sourceImage->rows;
    int numCols = this->sourceImage->cols;

    std::vector<int> xKernelRange{-1, 0, 1};
    std::vector<int> yKernelRange{-1, 0, 1};


    for (int x = 1; x < numCols - 1; x++) {
        for (int y = 1; y < numRows - 1; y++) {
            std::vector<int> neighbourHoodValues = aggregateNeighbourhood(x, y, xKernelRange, yKernelRange);
            int median = calculateMedianValueOfNeighbourhood(neighbourHoodValues);
            ( outputImage.get())->at<uchar>(y, x) = median;
        }

    }
    return outputImage;
}


std::vector<int> MedianFilter::aggregateNeighbourhood(int centerX, int centerY, std::vector<int> xKernelRange, std::vector<int> yKernelRange) {
    std::vector<int> pixelValues;
    for (int dx : xKernelRange) {
        for (int dy : yKernelRange) {
            int pixelX = centerX + dx;
            int pixelY = centerY + dy;
            auto value = static_cast<int>(this->sourceImage->at<uchar>(pixelY, pixelX));
            pixelValues.push_back(value);
        }
    }
    return pixelValues;
}

int MedianFilter::calculateMedianValueOfNeighbourhood(std::vector<int> values) {
    size_t n = values.size() / 2;
    std::sort(values.begin(), values.end());
    return values.at(n);
}

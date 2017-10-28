#include "MeanFilter.h"

std::unique_ptr<cv::Mat> MeanFilter::applyFilter() {
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
            int sum = calculateSumOfNeighbourhood(x, y, xKernelRange, yKernelRange);
            float average = calculateAverageofNeighbourhood(sum,
                                                            static_cast<int>(xKernelRange.size()),
                                                            static_cast<int>(yKernelRange.size())) ;
            ( outputImage.get())->at<uchar>(y, x) = average;
        }

    }

    return outputImage;
}


int MeanFilter::calculateSumOfNeighbourhood(int centerX, int centerY, std::vector<int> xKernelRange, std::vector<int> yKernelRange) {
    int sum = 0;
    for (int dx : xKernelRange) {
        for (int dy : yKernelRange) {
            int pixelX = centerX + dx;
            int pixelY = centerY + dy;
            auto value = static_cast<int>(this->sourceImage->at<uchar>(pixelY, pixelX));
            sum += value;
        }
    }
    return sum;
}

float MeanFilter::calculateAverageofNeighbourhood(int sum, int xKernelSize, int yKernelSize) {
    return (float) sum / (float) (xKernelSize * yKernelSize);
}
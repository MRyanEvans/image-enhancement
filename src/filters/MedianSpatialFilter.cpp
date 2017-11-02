#include "MedianSpatialFilter.h"

/**
 * Apply the median filter to the image.
 * @return The median filtered image.
 */
std::unique_ptr<cv::Mat> MedianSpatialFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );

    /**
     * We have to do more here than the other filters simply because a kernel convolution will not work.
     */
    int numRows = this->sourceImage->rows;
    int numCols = this->sourceImage->cols;

    // The offset from the center pixel to traverse.
    // Basically describing a kernel relative to the center pixel.
    std::vector<int> xKernelRange{-1, 0, 1};
    std::vector<int> yKernelRange{-1, 0, 1};

    // Loop over image pixels, making sure to skip the edges to get only full neighbourhoods.
    for (int x = 1; x < numCols - 1; x++) {
        for (int y = 1; y < numRows - 1; y++) {
            // Determine and set the median value of the neighbourhood.
            std::vector<int> neighbourHoodValues = aggregateNeighbourhood(x, y, xKernelRange, yKernelRange);
            int median = calculateMedianValueOfNeighbourhood(neighbourHoodValues);
            ( outputImage.get())->at<uchar>(y, x) = median;
        }

    }
    return outputImage;
}

/**
 * Aggregate the values of each pixel in the neighbourhood.
 * @param centerX The center point of the neighbourhood relative to the image's x axis.
 * @param centerY The center point of the neighbourhood relative to the image's y axis.
 * @param xKernelRange The kernel's horizontal descriptor.
 * @param yKernelRange The kernel's vertical descriptor.
 * @return A vector of the neighbourhood values.
 */
std::vector<int> MedianSpatialFilter::aggregateNeighbourhood(int centerX, int centerY, std::vector<int> xKernelRange, std::vector<int> yKernelRange) {
    std::vector<int> pixelValues;
    /**
     * Go over each kernel value;
     */
    for (int dx : xKernelRange) {
        for (int dy : yKernelRange) {
            // Find the selected neighbourhood pixel relative to the image and add it to our list.
            int pixelX = centerX + dx;
            int pixelY = centerY + dy;
            auto value = static_cast<int>(this->sourceImage->at<uchar>(pixelY, pixelX));
            pixelValues.push_back(value);
        }
    }
    return pixelValues;
}
/**
 * Determines the median value in a vector of pixel values.
 * @param values The list of pixel values.
 * @return The median value.
 */
int MedianSpatialFilter::calculateMedianValueOfNeighbourhood(std::vector<int> values) {
    size_t n = values.size() / 2;
    std::sort(values.begin(), values.end());
    return values.at(n);
}

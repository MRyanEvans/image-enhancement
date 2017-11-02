#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H


#include "SpatialDomainFilter.h"

/**
 * Applies a Median Filter to an image.
 * This uses the median value of the neighbourhood as the center pixel value.
 */
class MedianSpatialFilter : public SpatialDomainFilter {
public:
    explicit MedianSpatialFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "MedianSpatialFilter";
    }
private:
    std::vector<int>
    aggregateNeighbourhood(int centerX, int centerY, std::vector<int> xKernelRange, std::vector<int> yKernelRange);

    int calculateMedianValueOfNeighbourhood(std::vector<int> values);

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H

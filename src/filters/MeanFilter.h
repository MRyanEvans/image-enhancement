#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H


#include "SpatialDomainFilter.h"

class MeanFilter : public SpatialDomainFilter {
public:
    explicit MeanFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;

private:

    float calculateAverageofNeighbourhood(int sum, int xKernelSize, int yKernelSize);

    int calculateSumOfNeighbourhood(int centerX, int centerY, std::vector<int> xKernelRange, std::vector<int> yKernelRange);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H



#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H


#include "SpatialDomainFilter.h"

/**
 * Filter which applies a Gaussian filter to a given image.
 */
class GaussianSpatialFilter : public SpatialDomainFilter {
public:
    explicit GaussianSpatialFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "GaussianSpatialFilter";
    }
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H

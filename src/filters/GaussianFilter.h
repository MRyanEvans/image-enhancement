

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H


#include "SpatialDomainFilter.h"

/**
 * Filter which applies a Gaussian filter to a given image.
 */
class GaussianFilter : public SpatialDomainFilter {
public:
    explicit GaussianFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_GAUSSIANFILTER_H

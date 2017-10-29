#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H


#include "SpatialDomainFilter.h"

/**
 * Applies a low pass filter kernel to an image.
 */
class LowPassFilter : public SpatialDomainFilter {
public:
    explicit LowPassFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;

private:

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H

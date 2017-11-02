#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H


#include "SpatialDomainFilter.h"

/**
 * Applies a low pass filter kernel to an image.
 */
class LowPassSpatialFilter : public SpatialDomainFilter {
public:
    explicit LowPassSpatialFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "LowPassSpatialFilter";
    }
private:

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFILTER_H

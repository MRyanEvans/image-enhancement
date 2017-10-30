#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_HIGHPASSFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_HIGHPASSFILTER_H


#include "SpatialDomainFilter.h"

/**
 * A filter favouring higher-frequency values.
 * This is not likely to be useful for image smoothing/noise reduction but is interesting nonetheless.
 */
class HighPassFilter : public SpatialDomainFilter {
public:
    explicit HighPassFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "HighPassFilter";
    }
private:
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_HIGHPASSFILTER_H

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H


#include "SpatialDomainFilter.h"

class MedianFilter : public SpatialDomainFilter {
public:
    explicit MedianFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_MEDIANFILTER_H

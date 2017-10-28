#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H


#include "FilterInterface.h"

class SpatialDomainFilter : public FilterInterface {
public:
    explicit SpatialDomainFilter(const std::shared_ptr<cv::Mat> image) : FilterInterface(image) {};

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H

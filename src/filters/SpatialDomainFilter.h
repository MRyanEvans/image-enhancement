#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H


#include "FilterInterface.h"

/**
 * Dummy class to provide further abstraction of specifically spatial filters.
 */
class SpatialDomainFilter : public FilterInterface {
public:
    explicit SpatialDomainFilter(const std::shared_ptr<cv::Mat> image) : FilterInterface(image) {};

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_SPATIALDOMAINFILTER_H

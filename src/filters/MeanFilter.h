//
// Created by ryan on 28/10/17.
//

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H


#include "SpatialDomainFilter.h"

class MeanFilter : public SpatialDomainFilter {
public:
    explicit MeanFilter(const std::shared_ptr<cv::Mat> image) : SpatialDomainFilter(image) {};

    std::unique_ptr<cv::Mat> applyFilter() override;;

};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_MEANFILTER_H

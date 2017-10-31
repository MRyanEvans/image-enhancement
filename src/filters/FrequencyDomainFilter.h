

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H


#include "FilterInterface.h"

class FrequencyDomainFilter : public FilterInterface {
public:
    explicit FrequencyDomainFilter(const std::shared_ptr<cv::Mat> image) : FilterInterface(image) {};
    static const char* getName() {
        return "FrequencyDomainFilter";
    }
};

#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H

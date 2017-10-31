

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H


#include "FrequencyDomainFilter.h"

class LowPassFrequencyFilter : public FrequencyDomainFilter {
public:
    explicit LowPassFrequencyFilter(const std::shared_ptr<cv::Mat> image) : FrequencyDomainFilter(image) {}

    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "LowPassFrequencyFilter";
    }

private:

    void takeDFT(cv::Mat &source, cv::Mat &destination);

    void recenterDFT(cv::Mat &source);

    void prepareImageForDisplay(cv::Mat &source, cv::Mat &destination, bool recenter);

    void invertDFT(cv::Mat &source, cv::Mat &destination);

    std::unique_ptr<cv::Mat>runDFT(std::shared_ptr<cv::Mat> image);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H

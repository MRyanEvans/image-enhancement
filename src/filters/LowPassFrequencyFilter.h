

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H


#include "FrequencyDomainFilter.h"

/**
 * Applies a low pass filter in the frequency domain.
 */
class LowPassFrequencyFilter : public FrequencyDomainFilter {
public:
    explicit LowPassFrequencyFilter(const std::shared_ptr<cv::Mat> image) : FrequencyDomainFilter(image) {}

    static const char* getName() {
        return "LowPassFrequencyFilter";
    }

    void filterSpectrum(cv::Mat &spectrumMagnitude, cv::Mat &filteredSpectrum) override ;;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_LOWPASSFREQUENCYFILTER_H

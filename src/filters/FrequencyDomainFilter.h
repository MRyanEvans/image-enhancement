

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H


#include "FilterInterface.h"

/**
 * Applies a filter in the frequency domain.
 */
class FrequencyDomainFilter : public FilterInterface {
public:
    explicit FrequencyDomainFilter(const std::shared_ptr<cv::Mat> image) : FilterInterface(image) {};
    std::unique_ptr<cv::Mat> applyFilter() override;;
    static const char* getName() {
        return "FrequencyDomainFilter";
    }

protected:
    virtual void filterSpectrum(cv::Mat &spectrumMagnitude, cv::Mat &filteredSpectrum);
    void computeDFTofImage(cv::Mat &source, cv::Mat &destination);

    void recenterDFT(cv::Mat &source);

    void getMagnitudeOfComplexSpectrum(cv::Mat &source, cv::Mat &destination, bool recenter);

    void invertDFT(cv::Mat &source, cv::Mat &destination);
    void writeImageToFile(const char* base, const char *name, cv::Mat image);
};

#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_FREQUENCYDOMAINFILTER_H



#include <opencv/cv.hpp>
#include <map>
#include "LowPassFrequencyFilter.h"
#include "../Utilities.h"

/**
 * Run a low pass filter across a spectrum magnitude.
 * @param spectrumMagnitude The original Fourier spectrum magnitude.
 * @param filteredSpectrum The filtered spectrum magnitude.
 */
void LowPassFrequencyFilter::filterSpectrum(cv::Mat& spectrumMagnitude, cv::Mat& filteredSpectrum) {
    cv::Mat magnitudeFiltered(spectrumMagnitude.rows, spectrumMagnitude.cols, spectrumMagnitude.type());

    float threshold = 0.4f;
    float thresholdedValue;

    /*
     * Find all frequencies above our threshold in the original spectrum and remove them.
     */
    for (int x = spectrumMagnitude.cols; x >= 0; x--) {
        for (int y = spectrumMagnitude.rows - 1; y >= 0; y--) {
            float value = spectrumMagnitude.at<float>(y, x);
            // Keep frequencies below the threshold as they are
            if ( value <= threshold) {
                thresholdedValue = value;
            } else { // and remove all frequencies above the threshold
                thresholdedValue = 0.0f;
            }
            magnitudeFiltered.at<float>(y, x) = thresholdedValue;
        }
    }
    filteredSpectrum = magnitudeFiltered;
}
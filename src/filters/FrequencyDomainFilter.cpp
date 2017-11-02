#include <opencv2/core.hpp>
#include "FrequencyDomainFilter.h"
#include "../Utilities.h"

/**
 * Compute the Discrete Fourier Transform of an image.
 * @param source The original image to process.
 * @param destination The Fourier spectrum of the image in complex space.
 */
void FrequencyDomainFilter::computeDFTofImage(cv::Mat &source, cv::Mat &destination) {
    // First add a complex dimension to the input image
    cv::Mat complexPlanes[2] = {source, cv::Mat::zeros(source.size(), CV_32F)};
    cv::Mat complexImage;
    cv::merge(complexPlanes, 2, complexImage);

    // Now we can perform the actual DFT
    cv::Mat dftImage;
    dft(complexImage, dftImage, cv::DFT_COMPLEX_OUTPUT);
    destination = dftImage;
}

/**
 * Swaps the quadrants of the Fourier spectrum round so it is easier for humans to understand.
 * @param source The original spectrum image.
 */
void FrequencyDomainFilter::recenterDFT(cv::Mat &source) {
    int cx = source.cols / 2;
    int cy = source.rows / 2;

    // Top left
    cv::Mat q0(source, cv::Rect(0, 0, cx, cy));
    // Top right
    cv::Mat q1(source, cv::Rect(cx, 0, cx, cy));
    // Bottom left
    cv::Mat q2(source, cv::Rect(0, cy, cx, cy));
    // Bottom right
    cv::Mat q3(source, cv::Rect(cx, cy, cx, cy));

    // Swap top left and bottom right
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    // Swap top right and bottom left
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

/**
 * Determine the magnitude of a complex image so that it can be processed/filtered easily.
 * @param source The complex source.
 * @param destination The scalar result.
 * @param recenter Whether to perform quadrant swapping after computing the magnitude.
 */
void FrequencyDomainFilter::getMagnitudeOfComplexSpectrum(cv::Mat &source, cv::Mat &destination, bool recenter) {
    // Split the complex image into real and imaginary planes.
    cv::Mat splitArray[2] = {cv::Mat::zeros(source.size(), CV_32F), cv::Mat::zeros(source.size(), CV_32F)};
    cv::split(source, splitArray);

    // Take the real plane.
    cv::Mat dftMagnitude;
    cv::magnitude(splitArray[0], splitArray[1], dftMagnitude);

    // Normalise the scale of the image
    dftMagnitude += cv::Scalar::all(1);
    cv::log(dftMagnitude, dftMagnitude);
    cv::normalize(dftMagnitude, dftMagnitude, 0, 1, CV_MINMAX);

    // Swap the quadrants of the image
    if (recenter) {
        recenterDFT(dftMagnitude);
    }

    destination = dftMagnitude;
}

/**
 * Calculate the inverse of a given Fourier specturm.
 * @param source The Fourier spectrum.
 * @param destination The inverse image.
 */
void FrequencyDomainFilter::invertDFT(cv::Mat &source, cv::Mat &destination) {
    cv::Mat inverse;
    cv::idft(source, inverse, cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
    destination = inverse;
}

/**
 * Write a given image to disk.
 * @param base The name of the filter.
 * @param name The identifier of the image.
 * @param image The image to write.
 */
void FrequencyDomainFilter::writeImageToFile(const char *base, const char *name, cv::Mat image) {
    std::string filteredSpectrumFileName(base);
    filteredSpectrumFileName.append(name).c_str();

    // Convert from float to a writable scale
    cv::Mat correctedImage;
    image.convertTo(correctedImage, CV_8UC3, 255.0);

    Utilities::saveFilteredImage(correctedImage, filteredSpectrumFileName.c_str());
}

/**
 * Orchestrate the Fourier analysis, frequency filtering and inverse image processing.
 * @return The processed, filtered image.
 */
std::unique_ptr<cv::Mat> FrequencyDomainFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );

    // Convert image to real values for the fourier transform
    cv::Mat imageFloat;
    (*this->sourceImage.get()).convertTo(imageFloat, CV_32FC1, 1.0 / 255.0);

    cv::Mat dftOfImage;
    computeDFTofImage(imageFloat, dftOfImage);

    // Get the magnitude of the spectrum and swap the quadrants for output display purposes.
    cv::Mat dftMagnitude;
    getMagnitudeOfComplexSpectrum(dftOfImage, dftMagnitude, true);

    writeImageToFile(getName(), "_Spectrum", dftMagnitude);

    // Swap the quadrants back for processing.
    recenterDFT(dftMagnitude);

    // Apply our filter to the spectrum
    cv::Mat dftMagnitudeFiltered;
    filterSpectrum(dftMagnitude, dftMagnitudeFiltered);

    // Swap quadrants, write filtered spectrum magnitude to disk, and swap quadrants back.
    recenterDFT(dftMagnitudeFiltered);
    writeImageToFile(getName(), "_Filtered_Spectrum", dftMagnitudeFiltered);
    recenterDFT(dftMagnitudeFiltered);

    // Convert our filtered magnitude into complex space
    cv::Mat planes[2] = {cv::Mat::zeros(dftOfImage.size(), CV_32F), cv::Mat::zeros(dftOfImage.size(), CV_32F)};
    planes[0] = dftMagnitudeFiltered;
    cv::Mat kernelSpectrum;
    cv::merge(planes, 2, kernelSpectrum);

    // Merge our spectrums so they can be used for the inverse
    cv::Mat outputSpectrum;
    cv::mulSpectrums(dftOfImage, kernelSpectrum, outputSpectrum, cv::DFT_ROWS);

    // Inverse the spectrum, getting the magnitude as we're done processing and don't care about the complex plane anymore
    cv::Mat inverseDFT;
    invertDFT(outputSpectrum, inverseDFT);
    getMagnitudeOfComplexSpectrum(inverseDFT, inverseDFT, false);

    // Change scale from float 0..1 to 0..255 to be written to file correctly
    cv::Mat inverseDFTCorrectScale;
    inverseDFT.convertTo(inverseDFTCorrectScale, CV_8UC3, 255.0);

    return std::make_unique<cv::Mat>(inverseDFTCorrectScale);
}

/**
 * Dummy method to perform a filter on a spectrum.  Should be overridden with complete implementation by subclasses.
 * @param spectrumMagnitude The spectrum image.
 * @param filteredSpectrum The filtered spectrum image.
 */
void FrequencyDomainFilter::filterSpectrum(cv::Mat &spectrumMagnitude, cv::Mat &filteredSpectrum) {
    filteredSpectrum = spectrumMagnitude;
}



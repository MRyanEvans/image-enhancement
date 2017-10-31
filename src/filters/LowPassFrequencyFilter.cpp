

#include <opencv/cv.hpp>
#include <map>
#include "LowPassFrequencyFilter.h"
#include "../Utilities.h"

std::unique_ptr<cv::Mat> LowPassFrequencyFilter::applyFilter() {
    std::unique_ptr<cv::Mat> outputImage = std::make_unique<cv::Mat>(
            this->sourceImage.get()->rows,
            this->sourceImage.get()->cols,
            this->sourceImage.get()->type()
    );
    //TODO refactor and comment

    return runDFT(this->sourceImage);
}


void LowPassFrequencyFilter::takeDFT(cv::Mat &source, cv::Mat &destination) {

    cv::Mat imageComplex[2] = {source, cv::Mat::zeros(source.size(), CV_32F)};

    cv::Mat dftReady;

    cv::merge(imageComplex, 2, dftReady);

    cv::Mat dftImage;
    dft(dftReady, dftImage, cv::DFT_COMPLEX_OUTPUT);
    destination = dftImage;
}

void LowPassFrequencyFilter::recenterDFT(cv::Mat &source) {
    int cx = source.cols / 2;
    int cy = source.rows / 2;

    cv::Mat q0(source, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(source, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(source, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(source, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

}

void LowPassFrequencyFilter::prepareImageForDisplay(cv::Mat &source, cv::Mat &destination, bool recenter) {
    cv::Mat splitArray[2] = {cv::Mat::zeros(source.size(), CV_32F), cv::Mat::zeros(source.size(), CV_32F)};
    cv::split(source, splitArray);
    cv::Mat dftMagnitude;
    cv::magnitude(splitArray[0], splitArray[1], dftMagnitude);


    dftMagnitude += cv::Scalar::all(1);
    cv::log(dftMagnitude, dftMagnitude);

    cv::normalize(dftMagnitude, dftMagnitude, 0, 1, CV_MINMAX);

    if (recenter) {
        recenterDFT(dftMagnitude);
    }

    destination = dftMagnitude;
}

void LowPassFrequencyFilter::invertDFT(cv::Mat &source, cv::Mat &destination) {
    cv::Mat inverse;

    cv::idft(source, inverse, cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
    destination = inverse;
}

std::unique_ptr<cv::Mat> LowPassFrequencyFilter::runDFT(std::shared_ptr<cv::Mat> image) {
    cv::Mat imageFloat;
    (*image.get()).convertTo(imageFloat, CV_32FC1, 1.0 / 255.0);

    cv::Mat dftOfImage;
    takeDFT(imageFloat, dftOfImage);

    cv::Mat dftMagnitude;
    prepareImageForDisplay(dftOfImage, dftMagnitude, true);

    writeImageToFile("_Spectrum", dftMagnitude);

    recenterDFT(dftMagnitude);

    cv::Mat dftMagnitudeFiltered(dftMagnitude.rows, dftMagnitude.cols, dftMagnitude.type());
    for (int x = dftMagnitude.cols; x >= 0; x--) {
        for (int y = dftMagnitude.rows - 1; y >= 0; y--) {
            float value = dftMagnitude.at<float>(y, x);
            float lowerThreshold = 0.85f;
            float upperThreshold = 1.0f;
            float thresholdedValue;
            // Remove frequencies within our filter range
            if (value >= lowerThreshold && value <= upperThreshold) {
                thresholdedValue = 1.0f;
            } else { // and keep all others the same
                thresholdedValue = value;
            }
            dftMagnitudeFiltered.at<float>(y, x) = thresholdedValue;
        }
    }

    recenterDFT(dftMagnitudeFiltered);

    writeImageToFile("_Filtered_Spectrum", dftMagnitudeFiltered);

    recenterDFT(dftMagnitudeFiltered);

    cv::Mat planes[2] = {cv::Mat::zeros(dftOfImage.size(), CV_32F), cv::Mat::zeros(dftOfImage.size(), CV_32F)};
    planes[0] = dftMagnitudeFiltered;
    cv::Mat kernelSpectrum;
    cv::merge(planes, 2, kernelSpectrum);
    cv::Mat outputSpectrum;
    cv::mulSpectrums(dftOfImage, kernelSpectrum, outputSpectrum, cv::DFT_ROWS);

    cv::Mat inverseDFT;
    invertDFT(outputSpectrum, inverseDFT);
    prepareImageForDisplay(inverseDFT, inverseDFT, false);

    // Change scale from float 0..1 to 0..255 to be written to file correctly
    cv::Mat inverseDFTCorrectScale;
    inverseDFT.convertTo(inverseDFTCorrectScale, CV_8UC3, 255.0);

    return std::make_unique<cv::Mat>(inverseDFTCorrectScale);
}

void LowPassFrequencyFilter::writeImageToFile(const char *name, cv::Mat image) {
    std::string filteredSpectrumFileName(getName());
    filteredSpectrumFileName.append(name).c_str();
    cv::Mat correctedImage;
    image.convertTo(correctedImage, CV_8UC3, 255.0);
    Utilities::saveFilteredImage(correctedImage, filteredSpectrumFileName.c_str());
}

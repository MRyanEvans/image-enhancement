
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv/cv.hpp>
#include <map>
#include <fstream>
#include "ImageEnhancer.h"
#include "filters/MedianFilter.h"
#include "filters/LowPassFilter.h"
#include "filters/HighPassFilter.h"
#include "filters/GaussianFilter.h"

using namespace std;


void displayImage(std::string windowName, cv::Mat image) {
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, image);
}

void takeDFT(cv::Mat &source, cv::Mat &destination) {

    cv::Mat imageComplex[2] = {source, cv::Mat::zeros(source.size(), CV_32F)};

    cv::Mat dftReady;

    cv::merge(imageComplex, 2, dftReady);

    cv::Mat dftImage;
    dft(dftReady, dftImage, cv::DFT_COMPLEX_OUTPUT);
    destination = dftImage;
}

void recenterDFT(cv::Mat &source) {
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

void prepareImageForDisplay(cv::Mat &source, cv::Mat &destination, bool recenter) {
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

void invertDFT(cv::Mat &source, cv::Mat &destination) {
    cv::Mat inverse;

    cv::idft(source, inverse, cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
    destination = inverse;
}

void runDFT(cv::Mat image) {

    cv::Mat imageFloat;
    image.convertTo(imageFloat, CV_32FC1, 1.0 / 255.0);

    cv::Mat dftOfImage;
    takeDFT(imageFloat, dftOfImage);

    cv::Mat dftMagnitude;
    prepareImageForDisplay(dftOfImage, dftMagnitude, true);
    displayImage("DFT", dftMagnitude);
    recenterDFT(dftMagnitude);

    cv::Mat dftMagnitudeFiltered(dftMagnitude.rows, dftMagnitude.cols, dftMagnitude.type());
    for (int x = dftMagnitude.cols; x >= 0; x--) {
        for (int y = dftMagnitude.rows - 1; y >= 0; y--) {
            float value = dftMagnitude.at<float>(y, x);
            float lowerThreshold = 0.75f;
            float upperThreshold = 1.0f;
            float thresholdedValue;
            // Remove frequencies within our filter range
            if (value >= lowerThreshold && value <= upperThreshold ) {
                thresholdedValue = 1.0f;
            } else { // and keep all others the same
                thresholdedValue = value;
            }
            dftMagnitudeFiltered.at<float>(y, x) = thresholdedValue;
        }
    }

    recenterDFT(dftMagnitudeFiltered);
    displayImage("Filtered DFT Magnitude", dftMagnitudeFiltered);
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


    displayImage("Inverse DFT", inverseDFT);
    displayImage("Original", image);


    cv::waitKey(0);

}


/**
 * Orchestrate the image reading and filtering.
 * @return Whether the processing completed successfully.
 */
int ImageEnhancer::run() {
//  Read both noisy and
    string filename = "resources/images/PandaNoise.bmp";
    auto image = make_shared<cv::Mat>(cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE));

    if (!image.get()->data) {
        cout << "Could not open image:  " << filename << endl;
        return -1;
    }

    string originalImageFilename = "resources/images/PandaOriginal.bmp";
    cv::Mat originalImage = cv::imread(originalImageFilename, CV_LOAD_IMAGE_GRAYSCALE);

    if (!originalImage.data) {
        cout << "Could not open image:  " << filename << endl;
        return -1;
    }

    runDFT(*(image.get()));
    /*
     * Apply all filters to the image.
     */
    unique_ptr<MedianFilter> medianFilter = make_unique<MedianFilter>(image);
    auto medianFilteredImage = *(medianFilter.get())->applyFilter();

    unique_ptr<LowPassFilter> lowPassFilter = make_unique<LowPassFilter>(image);
    auto lowPassFilteredImage = *(lowPassFilter.get())->applyFilter();

    unique_ptr<HighPassFilter> highPassFilter = make_unique<HighPassFilter>(image);
    auto highPassFilteredImage = *(highPassFilter.get())->applyFilter();

    unique_ptr<GaussianFilter> gaussianFilter = make_unique<GaussianFilter>(image);
    auto gaussianFilteredImage = *(gaussianFilter.get())->applyFilter();

    map<const char *, cv::Mat> filteredImages;

    // Add the filtered images to a map for further processing
    filteredImages[MedianFilter::getName()] = medianFilteredImage;
    filteredImages[LowPassFilter::getName()] = lowPassFilteredImage;
    filteredImages[HighPassFilter::getName()] = highPassFilteredImage;
    filteredImages[GaussianFilter::getName()] = gaussianFilteredImage;

    saveImagesToDisk(filteredImages);

    calculateMSEsComparedToOriginal(filteredImages, originalImage);

    return 0;
}


/**
 * Calculate the Mean Square Error (MSE) of the modified (noise-filtered) image compared to the original image.
 * @param originalImage The image before the artificial noise was applied.
 * @param modifiedImage The filtered noisy image.
 * @return The MSE of the filtered image.
 */
float ImageEnhancer::calculateMeanSquareError(cv::Mat *originalImage, cv::Mat *modifiedImage) {
    float mse;
    int M = originalImage->cols;
    int N = originalImage->rows;
    int sumSquaredError = 0;
    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            // sse = (f(x,y) - f'(x,y))^2
            int valueOriginal = originalImage->at<uchar>(y, x);
            int valueModified = modifiedImage->at<uchar>(y, x);
            int error = valueOriginal - valueModified;
            sumSquaredError += (error * error);
        }
    }
    // Average the sum of errors by the image size
    mse = (float) sumSquaredError / (float) (M * N);
    return mse;
}

/**
 * Writes a map of processed images to disk.
 * @param images The map of images to save.
 */
void ImageEnhancer::saveImagesToDisk(map<const char *, cv::Mat> images) {
    for (auto const &entry : images) {
        saveFilteredImage(entry.second, entry.first);
    }
}

/**
 * Writes a given image to disk.
 * @param image The image to write.
 * @param filename The name of the file to write (excluding file extension).
 */
void ImageEnhancer::saveFilteredImage(const cv::Mat image, const std::string filename) {
    string path = "output/" + filename + ".png";
    cv::imwrite(path, image);
}

/**
 * Calculates and outputs the Mean Squared Errors for a map of filtered images.
 * @param filteredImages The map of processed images.
 * @param originalImage The unmodified image used to calculated MSEs.
 */
void ImageEnhancer::calculateMSEsComparedToOriginal(map<const char *, cv::Mat> filteredImages, cv::Mat originalImage) {

    std::ofstream mseOutput("output/mse.csv");
    mseOutput << "FILTER" << "," << "MSE" << endl;
    for (auto &entry : filteredImages) {
        float mse = calculateMeanSquareError(&originalImage, &(entry.second));
        cout << "Mean Squared Error of " << entry.first << ":  " << mse << endl;
        mseOutput << entry.first << "," << mse << endl;
    }
    mseOutput.close();
}



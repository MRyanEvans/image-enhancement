
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

    map<const char*, cv::Mat> filteredImages;

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
void ImageEnhancer::saveImagesToDisk(map<const char*, cv::Mat> images) {
    for (auto const& entry : images ) {
        saveFilteredImage(entry.second, entry.first);
    }
}
/**
 * Writes a given image to disk.
 * @param image The image to write.
 * @param filename The name of the file to write (excluding file extension).
 */
void ImageEnhancer::saveFilteredImage(const cv::Mat image, const std::string filename) {
    string path = "output/" + filename + ".bmp";
    cv::imwrite(path, image);
}

/**
 * Calculates and outputs the Mean Squared Errors for a map of filtered images.
 * @param filteredImages The map of processed images.
 * @param originalImage The unmodified image used to calculated MSEs.
 */
void  ImageEnhancer::calculateMSEsComparedToOriginal(map<const char*, cv::Mat> filteredImages, cv::Mat originalImage) {

    std::ofstream mseOutput("output/mse.csv");
    mseOutput << "FILTER" << "," << "MSE" << endl;
    for (auto & entry : filteredImages ) {
        float mse = calculateMeanSquareError(&originalImage, &(entry.second));
        cout << "Mean Squared Error of " << entry.first << ":  " << mse << endl;
        mseOutput << entry.first << "," << mse << endl;
    }
    mseOutput.close();
}



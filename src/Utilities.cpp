

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include <opencv/cv.hpp>
#include "Utilities.h"

/**
 * Calculate the Mean Square Error (MSE) of the modified (noise-filtered) image compared to the original image.
 * @param originalImage The image before the artificial noise was applied.
 * @param modifiedImage The filtered noisy image.
 * @return The MSE of the filtered image.
 */
float Utilities::calculateMeanSquareError(cv::Mat *originalImage, cv::Mat *modifiedImage) {
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
void Utilities::saveImagesToDisk(std::map<const char *, cv::Mat> images) {
    for (auto const &entry : images) {
        saveFilteredImage(entry.second, entry.first);
    }
}

/**
 * Writes a given image to disk.
 * @param image The image to write.
 * @param filename The name of the file to write (excluding file extension).
 */
void Utilities::saveFilteredImage(const cv::Mat image, const std::string filename) {
    std::string path = "output/" + filename + ".png";
    cv::imwrite(path, image);
}


/**
 * Calculates and outputs the Mean Squared Errors for a map of filtered images.
 * @param filteredImages The map of processed images.
 * @param originalImage The unmodified image used to calculated MSEs.
 */
void Utilities::calculateMSEsComparedToOriginal(std::map<const char *, cv::Mat> filteredImages, cv::Mat originalImage) {

    std::ofstream mseOutput("output/mse.csv");
    mseOutput << "FILTER" << "," << "MSE" << std::endl;
    for (auto &entry : filteredImages) {
        float mse = calculateMeanSquareError(&originalImage, &(entry.second));
        std::cout << "Mean Squared Error of " << entry.first << ":  " << mse << std::endl;
        mseOutput << entry.first << "," << mse << std::endl;
    }
    mseOutput.close();
}



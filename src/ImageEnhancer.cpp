
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv/cv.hpp>
#include "ImageEnhancer.h"
#include "filters/MedianFilter.h"
#include "filters/MeanFilter.h"
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

    //TODO put these into a map/vector

    unique_ptr<MedianFilter> medianFilter = make_unique<MedianFilter>(image);
    auto medianFilteredImage = *(medianFilter.get())->applyFilter();

    unique_ptr<MeanFilter> meanFilter = make_unique<MeanFilter>(image);
    auto meanFilteredImage = *(meanFilter.get())->applyFilter();

    unique_ptr<HighPassFilter> highPassFilter = make_unique<HighPassFilter>(image);
    auto highPassFilteredImage = *(highPassFilter.get())->applyFilter();

    unique_ptr<GaussianFilter> gaussianFilter = make_unique<GaussianFilter>(image);
    auto gaussianFilteredImage = *(gaussianFilter.get())->applyFilter();

    //TODO read from a map/vector to display images

    string originalImageWindowName = "Original Image";

    cv::namedWindow(originalImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(originalImageWindowName, originalImage);

    string noisyImageWindowName = "Image with Noise";

    cv::namedWindow(noisyImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(noisyImageWindowName, *(image.get()));

    string medianFilteredImageWindowName = "Median Filtered Image";

    cv::namedWindow(medianFilteredImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(medianFilteredImageWindowName, medianFilteredImage);


    string meanFilteredImageWindowName = "Mean Filtered Image";

    cv::namedWindow(meanFilteredImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(meanFilteredImageWindowName, meanFilteredImage);

    string highPassFilteredImageWindowName = "High Pass Filtered Image";

    cv::namedWindow(highPassFilteredImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(highPassFilteredImageWindowName, highPassFilteredImage);

    string gaussianFilteredImageWindowName = "Gaussian Filtered Image";

    cv::namedWindow(gaussianFilteredImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(gaussianFilteredImageWindowName, gaussianFilteredImage);

    //TODO read from a map/vector to display MSEs
    float mse = calculateMeanSquareError(&originalImage, &gaussianFilteredImage);
    cout << "Mean Squared Error of " << gaussianFilteredImageWindowName << ":  " << mse << endl;

    cv::waitKey(0);

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

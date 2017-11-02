
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv/cv.hpp>
#include <map>
#include "ImageEnhancer.h"
#include "filters/MedianSpatialFilter.h"
#include "filters/LowPassSpatialFilter.h"
#include "filters/GaussianSpatialFilter.h"
#include "filters/LowPassFrequencyFilter.h"
#include "Utilities.h"

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
    unique_ptr<MedianSpatialFilter> medianFilter = make_unique<MedianSpatialFilter>(image);
    auto medianFilteredImage = *(medianFilter.get())->applyFilter();

    unique_ptr<LowPassSpatialFilter> lowPassFilter = make_unique<LowPassSpatialFilter>(image);
    auto lowPassFilteredImage = *(lowPassFilter.get())->applyFilter();

    unique_ptr<GaussianSpatialFilter> gaussianFilter = make_unique<GaussianSpatialFilter>(image);
    auto gaussianFilteredImage = *(gaussianFilter.get())->applyFilter();

    unique_ptr<LowPassFrequencyFilter> lowPassFrequencyFilter = make_unique<LowPassFrequencyFilter>(image);
    auto lowPassFrequencyFilteredImage = *(lowPassFrequencyFilter.get())->applyFilter();

    map<const char *, cv::Mat> filteredImages;

    // Add the filtered images to a map for further processing
    filteredImages[MedianSpatialFilter::getName()] = medianFilteredImage;
    filteredImages[LowPassSpatialFilter::getName()] = lowPassFilteredImage;
    filteredImages[GaussianSpatialFilter::getName()] = gaussianFilteredImage;
    filteredImages[LowPassFrequencyFilter::getName()] = lowPassFrequencyFilteredImage;

    Utilities::saveImagesToDisk(filteredImages);

    Utilities::calculateMSEsComparedToOriginal(filteredImages, originalImage);

    return 0;
}




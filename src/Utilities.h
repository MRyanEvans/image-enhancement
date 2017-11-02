

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_UTILITIES_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_UTILITIES_H

#include <map>

class Utilities {
public:
    static float calculateMeanSquareError(cv::Mat *originalImage, cv::Mat *modifiedImage);

    static void saveFilteredImage(const cv::Mat image, const std::string filename);

    static void saveImagesToDisk(std::map<const char *, cv::Mat> images);

    static void calculateMSEsComparedToOriginal(std::map<const char *, cv::Mat> filteredImages, cv::Mat originalImage);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_UTILITIES_H



#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H

#include <map>
class ImageEnhancer {
public:
    int run();
private:
    float calculateMeanSquareError(cv::Mat *originalImage, cv::Mat *modifiedImage);
    void saveFilteredImage(const cv::Mat image, const std::string filename) ;
    void saveImagesToDisk(std::map<const char*, cv::Mat> images);
    void calculateMSEsComparedToOriginal(std::map<const char*, cv::Mat> filteredImages, cv::Mat originalImage);
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H



#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H

class ImageEnhancer {
public:
    int run();
private:
    float calculateMeanSquareError(cv::Mat *originalImage, cv::Mat *modifiedImage);
    void saveFilteredImage(const cv::Mat image, const std::string filename) ;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_IMAGEENHANCER_H

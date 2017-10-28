//
// Created by ryan on 28/10/17.
//

#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H


#include <opencv2/core/mat.hpp>
#include <memory>

class FilterInterface {
public:
    explicit FilterInterface(const std::shared_ptr<cv::Mat> image) {
        this->sourceImage = image;
    }
    virtual std::unique_ptr<cv::Mat> applyFilter() = 0;

protected:
    std::shared_ptr<cv::Mat> sourceImage;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H

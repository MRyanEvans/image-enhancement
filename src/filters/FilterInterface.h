
#ifndef IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H
#define IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H


#include <opencv2/core/mat.hpp>
#include <memory>

/**
 * Interface for applying a filter to an image.
 */
class FilterInterface {
public:
    /**
     * Constructs a new filter with an image reference.
     * @param image The image on which the filter will be applied.
     */
    explicit FilterInterface(const std::shared_ptr<cv::Mat> image) {
        this->sourceImage = image;
    }
    /**
     * Applies the filter to the image.
     * @return A pointer to a new filtered image.
     */
    virtual std::unique_ptr<cv::Mat> applyFilter() = 0;

    static const char* getName() {
        return "FilterInterface";
    }
protected:
    std::shared_ptr<cv::Mat> sourceImage;
};


#endif //IMAGE_ENHANCEMENT_IMPLEMENTATION_FILTERINTERFACE_H

#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageEnhancer.h"

using namespace std;
using namespace cv;



int main() {
    ImageEnhancer imageEnhancer;
    return imageEnhancer.run();

}


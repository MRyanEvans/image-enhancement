#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;




int main() {
    const char *filename = "resources/images/PandaNoise.bmp";
    cv::Mat image = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data) {
        cout << "Could not open image:  " << filename << endl;
        return -1;
    }


    string noisyImageWindowName = "Image with Noise";

    cv::namedWindow(noisyImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(noisyImageWindowName, image);


    cv::waitKey(0);

    return 0;
}


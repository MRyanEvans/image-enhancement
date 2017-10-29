#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageEnhancer.h"

using namespace std;
using namespace cv;


void padimage(cv::Mat src, cv::Mat dest) {
    cv::Mat padded;
    int m = cv::getOptimalDFTSize(src.rows);
    int n = cv::getOptimalDFTSize(src.cols);
    cv::copyMakeBorder(src, dest, 0, m - src.rows, 0, n - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
}

Mat buildKernel() {
    return Mat::ones(2, 2, CV_32F) / (float) 5.25;
}

void runDFT(Mat image) {

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize(image.rows);
    int n = getOptimalDFTSize(image.cols); // on the border add zero values
    copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    Mat dftOutput;
    dft(complexI, dftOutput);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(image))^2 + Im(DFT(image))^2))
    split(dftOutput, planes);                   // planes[0] = Re(DFT(image), planes[1] = Im(DFT(image))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];
//
//    Mat magIDisplay = planes[0] + Scalar::all(1);                    // switch to logarithmic scale
//    log(magIDisplay, magIDisplay);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).



//    Mat kernel = (Mat_<double>(3,3) <<  1.36, 0.062,  -0.921,
//            -0.644198,  1.10, -0.17,
//            -0.072951, -1.81485,  2.806);
//
//    Mat convolved;
//    multiply(dftOutput, dftKernel, convolved);

    cv::Mat inverseTransform;
//    idft(convolved, inverseTransform, DFT_REAL_OUTPUT);


    const char *inverseDftWindowName = "Inverse DFT";

    cv::namedWindow(inverseDftWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(inverseDftWindowName, inverseTransform);

}

int main() {
    ImageEnhancer imageEnhancer;
    return imageEnhancer.run();

}


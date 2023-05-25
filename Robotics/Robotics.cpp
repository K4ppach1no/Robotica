#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

Mat blur_difference(Mat img, int h1, int s1, int h2, int s2)
{
    Mat b1, b2, dif;
    GaussianBlur(img, b1, Size(h1, h1), s1);
    GaussianBlur(img, b2, Size(h2, h2), s2);

    dif = b1 - b2;

    return dif;
}

int main()
{
    std::string img_path = R"(IMG20230516092711.jpg)"; //TODO: delete bard picture
    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    Mat grey,thr;
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    cv::resize(img, img, {500, 500}, 0, 0, cv::INTER_NEAREST);
    cv::cvtColor(img, grey, COLOR_BGR2GRAY);
    threshold(blur_difference(grey, 7, 7, 17, 13), thr, 1, 255, THRESH_BINARY);
    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    //cv::imshow("img", img);
    std::cout << contours.size()<< std::endl;
    cv::waitKey(0);
    std::cout << "Hello World!\n";
}

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    std::string img_path = R"(../bard.png)"; //TODO: delete bard picture
    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    cv::resize(img, img, {500, 500}, 0, 0, cv::INTER_NEAREST);
    cv::imshow("img", img);
    cv::waitKey(0);
    std::cout << "Hello World!\n";
}

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int imageX = 500;
int imageY = 500;

cv::Mat loadImage(std::string img_path) {
    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    cv::resize(img, img, { imageX, imageY }, 0, 0, cv::INTER_NEAREST);
    return img;
}

cv::Mat imagePrep(cv::Mat img) {
    cv::Mat greyMat, blur,thresh;
    cv::resize(img, img, { imageX, imageY }, 0, 0, cv::INTER_NEAREST);
    cv::cvtColor(img, greyMat, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(greyMat, blur, cv::Size(5, 5), 1);
    cv::adaptiveThreshold(blur, thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
    return thresh;
}

int main()
{
    cv::Mat img = loadImage(R"(C:\Users\Alissa\Documents\Stenden\robotica\testcases-photo\test30.jpg)");
    cv::Mat imgEnv = loadImage(R"(C:\Users\Alissa\Documents\Stenden\robotica\testcases-photo\test29.jpg)");
    cv::Mat thresh, threshEnv, masked;
    
    //prepares the mask for the background 
    threshEnv=imagePrep(imgEnv);

    thresh= imagePrep(img);

    
    //layers the mask on top of the threshold picture,
    cv::bitwise_not(thresh, masked, threshEnv);

    #pragma region contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(masked, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    //since x and y need to be the smallest numbers they will be put at the max image size, 
    //so its only supposed to go down but if it starts at zero it will never go up to the actual smallest one
    //w and h are going to become big numbers so they should start from zero
    int x = imageX, y = imageY, w = 0, h = 0;
    //loops through every contour to check their area
    for (int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        //if the area is to small it will not be included
        if (area > 50) {
            //create bounding box for the contours
            cv::Rect rect = cv::boundingRect(contours[i]);
            //ignore outline of big box at the corners
            if (rect.area() < (imageX*imageY)) {
                //the following if statements are meant to check what the outer most corners are of all the boxes combined
                //these outer corners will be the corners of the main box surounding the medicine box
                if (rect.x < x) {
                    x = rect.x;
                }
                if (rect.y < y)
                {
                    y = rect.y;
                }
                //since height and width are relative and are not always the longest 
                //we add them to their x or y counter parts to get the largest and furthest most point
                if (rect.height + rect.y > h) {
                    h = rect.height + rect.y;
                }
                if (rect.width + rect.x > w)
                {
                    w = rect.width + rect.x;
                }
            }
        }
    }

    //because w is actual width but just the furthest x point we subtract the x of the box
    //because h is actual height but just the furthest y point we subtract the y of the box
    w = w-x;
    h = h-y;

    //create rectangle with new variables and draw
    cv::Rect medicine = cv::Rect(x, y, w, h);
    cv::rectangle(img, medicine, (255, 20, 20), 1);

    //some info into the output window thingy
    std::cout << "Het medicijn doosje is op  x: "<<medicine.x<<", op y: " << medicine.y << ", met een breedte van: " << medicine.width << ", een hoogte van: " << medicine.height << " en een totaal oppervlak van : "<<medicine.area();

#pragma endregion

    cv::imshow("img", img);
    cv::imshow("thresh set value", threshEnv);
    cv::imshow("thresh using adapt gausian", thresh);
    cv::imshow("masked", masked);


    cv::waitKey(0);
    std::cout << "Hello World!\n";

}
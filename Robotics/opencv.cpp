//#include "pch.h"
#include "opencv.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cassert>

#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void opencv::detect_object(Mat img)
{
    RNG rng(12345);
    Mat grey, thr;
    Point2f box[4];
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int hierarchy_size = 0;
    int main_box = -1;

    // Resize and convert the image to grayscale
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    cvtColor(img, grey, COLOR_BGR2GRAY);

    // Threshold the grayscale image using a blur difference method
    threshold(blur_difference(grey, 7, 7, 17, 13), thr, 1, 255, THRESH_BINARY);

    // Find contours and hierarchy of the thresholded image
    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));//TODO uncomment for rasp

    // Iterate over each contour
    for (size_t i = 0; i < contours.size(); i++)
    {
        //color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        //drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        //if the contours dont have any parents(-1), has a area bigger than 1500 and has a certain percentage thats equal to a square
        if (contourArea(contours[i]) > 1500 && hierarchy[i][3] == -1&& area_rotated_percentage(contours[i]) > 30) {

        // Calculate the contour area and rotated area percentage
        float contour_area = contourArea(contours[i]);
        float contour_area_rotated_percentage = area_rotated_percentage(contours[i]);

        // Check conditions for the contour to be considered as the main object
        if (contour_area > 1500 && hierarchy[i][3] == -1 && contour_area_rotated_percentage > 30) {
            int a = 0;
            float contour_y_area_rotated_percentage = area_rotated_percentage(contours[i]);
            float contour_y_area = contourArea(contours[i]);

            // Iterate over the hierarchy to find children contours
            for (int y = 0; y < hierarchy.size(); y++) {
                if (hierarchy[y][3] == i && contour_y_area_rotated_percentage > 30 && contour_y_area > 500) {
                    a++;
                    if (a > hierarchy_size) {
                        hierarchy_size = a;
                        main_box = i;
                        break; // Exit the loop since we have found a larger hierarchy
                    }
                }
            }
        }
    }

    if (main_box == -1) { //as long as the main_box = -1 they will not draw other wise it will start drawing a box around 0 because it could not find the correct one
        imshow("img", img);//TODO uncomment for rasp
        return;
    }


    //draw rotated box that fits description
    RotatedRect rotated_rect = minAreaRect(contours[main_box]);
    rotated_rect.points(box);
    int rotatedarea = rotated_rect.size.width * rotated_rect.size.height;
    
    //TODO uncomment for rasp
    for (int i = 0; i < 4; i++) { //because box cant be drawen using rectangle, get ev3ry point and draw lines between each point
        line(img, box[i], box[(i + 1) % 4], color);
    }

    // Draw center
    // circle(img, rotated_rect.center, 2, color, FILLED, LINE_8);

    // Print information about the main object
    cout << rotated_rect.center << endl;
    cout << rotated_rect.angle << endl;
    cout << "size of rotated area: " << rotated_area << endl;
    cout << contourArea(contours[main_box]) << endl;
    cout << "size of rotated area percentage: " << contourArea(contours[main_box]) * (100.0 / rotated_area) << endl;
    cout << hierarchy_size << " " << endl;
    cout << "move to x: " << 250 - rotated_rect.center.x << " and y: " << rotated_rect.center.y - 250 << endl;

    // imshow("img", img);
}

Mat opencv::blur_difference(Mat img, int h1, int s1, int h2, int s2)
{
    Mat b1, b2, dif;

    // Apply Gaussian blur with specified parameters
    GaussianBlur(img, b1, Size(h1, h1), s1);
    GaussianBlur(img, b2, Size(h2, h2), s2);

    // Calculate the difference between the blurred images
    dif = b1 - b2;

    return dif;
}

float opencv::area_rotated_percentage(vector<Point> contour)
{
    // Calculate the rotated bounding box and its area
    RotatedRect rotated_rect = minAreaRect(contour);
    int rotated_area = rotated_rect.size.width * rotated_rect.size.height;

    // Calculate the contour area percentage with respect to the rotated area
    return contourArea(contour) * (100.0 / rotated_area);
}

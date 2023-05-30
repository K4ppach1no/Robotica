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

    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));//TODO uit rasp

    // Iterate over each contour
    for (size_t i = 0; i < contours.size(); i++)
    {
        // color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        // drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

        // Calculate the contour area and rotated area percentage
        float contour_area = contourArea(contours[i]);
        float contour_area_rotated_percentage = area_rotated_percentage(contours[i]);

        // Check conditions for the contour to be considered as the main object
        if (contour_area > 1500 && hierarchy[i][3] == -1 && contour_area_rotated_percentage > 30) {
            int a = 0;

            // Iterate over the hierarchy to find children contours
            for (int y = i+1; y < hierarchy.size(); y++) {
                float contour_y_area_rotated_percentage = area_rotated_percentage(contours[y]);
                float contour_y_area = contourArea(contours[y]);
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

    if (main_box == -1) {
        // No main object found, return
        imshow("img", img); //TODO uit rasp
        return;
    }

    // Draw rotated box that fits the description
    RotatedRect rotated_rect = minAreaRect(contours[main_box]);
    rotated_rect.points(box);
    int rotated_area = rotated_rect.size.width * rotated_rect.size.height;

    
    for (int i = 0; i < 4; i++) {//TODO uit rasp
        // Draw lines between each point to form the rotated box
        line(img, box[i], box[(i + 1) % 4], color);
    }

    // Draw center
    circle(img, rotated_rect.center, 2, color, FILLED, LINE_8);//TODO uit rasp

    // Print information about the main object
    cout << rotated_rect.center << endl;
    cout << rotated_rect.angle << endl;
    cout << "size of rotated area: " << rotated_area << endl;
    cout << contourArea(contours[main_box]) << endl;
    cout << "size of rotated area percentage: " << contourArea(contours[main_box]) * (100.0 / rotated_area) << endl;
    cout << hierarchy_size << " " << endl;
    cout << "move to x: " << 250 - rotated_rect.center.x << " and y: " << rotated_rect.center.y - 250 << endl;

    imshow("img", img);//TODO uit rasp
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

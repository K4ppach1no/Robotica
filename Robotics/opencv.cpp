//#include "pch.h"
#include "opencv.h"


#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

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

    int hierachy_size = 0;
    int main_box = -1;

    //img prep
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    cvtColor(img, grey, COLOR_BGR2GRAY);
    threshold(blur_difference(grey, 7, 7, 17, 13), thr, 1, 255, THRESH_BINARY);
    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));//TODO uncomment for rasp

    for (size_t i = 0; i < contours.size(); i++)
    {
        //color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        //drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        //if the contours dont have any parents(-1), has a area bigger than 1500 and has a certain percentage thats equal to a square
        if (contourArea(contours[i]) > 1500 && hierarchy[i][3] == -1&& area_rotated_percentage(contours[i]) > 30) {

            int a = 0;
            for (int y = i+1; y < hierarchy.size(); y++) {
                //due to the fact that childeren, grandchilderen etc come right after the parent we can just start the for loop at the index + 1 
                //to in worst case have 1 less loop to check in best.
                if (hierarchy[y][3] == i&& area_rotated_percentage(contours[y]) > 30 && contourArea(contours[y]) > 500) {
                    a++;
                }
            }

            if (a > hierachy_size) { //choose object with highest amounts of kids that are also boxes
                hierachy_size = a;
                main_box = i;
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

    //center
    circle(img, rotated_rect.center, 2, color, FILLED, LINE_8); //TODO uncomment for rasp

    //checks and info
    cout << rotated_rect.center << endl;
    cout << rotated_rect.angle << endl;
    cout << "size of rotated area : " << rotatedarea << endl;
    cout << contourArea(contours[main_box])  << endl;
    cout << "size of rotated area percentage: " << contourArea(contours[main_box]) * (100.0 / rotatedarea)<< endl;
    cout << hierachy_size << " " << endl;
    cout << "move to x : " << 250 - rotated_rect.center.x << " and y : " << rotated_rect.center.y - 250 << endl; //use to determine how much the arm needs to rotate?
   
    imshow("img", img); //TODO uncomment for rasp

}

Mat opencv::blur_difference(Mat img, int h1, int s1, int h2, int s2)
{
    Mat b1, b2, dif;
    GaussianBlur(img, b1, Size(h1, h1), s1);
    GaussianBlur(img, b2, Size(h2, h2), s2);

    dif = b1 - b2;

    return dif;
}

float opencv::area_rotated_percentage(vector<Point> contour)
{
    RotatedRect rotated_rect = minAreaRect(contour);
    int rotatedarea = rotated_rect.size.width * rotated_rect.size.height;
    return contourArea(contour) * (100.0 / rotatedarea);;
}



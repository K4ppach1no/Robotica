#include "pch.h"
#include "opencv.h"

void opencv::detect_object(Mat img)
{
    RNG rng(12345);
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    Mat grey, thr, adthr;
    Point2f box[4];

    cvtColor(img, grey, COLOR_BGR2GRAY);

    threshold(blur_difference(grey, 7, 7, 17, 13), thr, 1, 255, THRESH_BINARY);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy,approx;
    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    int hierachy_size = 0;
    int main_box = -1;
    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

    for (size_t i = 0; i < contours.size(); i++)
    {
        //color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        //drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        if (contourArea(contours[i]) > 1500 && hierarchy[i][3] == -1&& area_rotated_percentage(contours[i]) > 50) {

            int a = 0;
            for (int y = 0; y < hierarchy.size(); y++) {
                if (hierarchy[y][3] == i&& area_rotated_percentage(contours[y]) > 50 && contourArea(contours[y]) > 500) {
                    a++;
                }
            }

            if (a > hierachy_size) { 
                hierachy_size = a;
                main_box = i;
            }
        }
    }

    if (main_box == -1) { //as long as the main_box = -1 they will not draw other wise it will start drawing a box around 0 because it could not find the correct one
        imshow("img", img);
        return;
    }

    RotatedRect rotated_rect = minAreaRect(contours[main_box]);
    rotated_rect.points(box);
    for (int i = 0; i < 4; i++) {
        line(img, box[i], box[(i + 1) % 4], color);
    }

    int rotatedarea = rotated_rect.size.width * rotated_rect.size.height;
    circle(img, rotated_rect.center, 2, color, FILLED, LINE_8);

    //Mat cropped_image = img(Range(rect.y, rect.y + rect.height), Range(rect.x, rect.x + rect.width));
    //resize(cropped_image, cropped_image, { 500, 500 }, 0, 0, INTER_NEAREST);

    cout << rotated_rect.center << endl;
    cout << rotated_rect.angle << endl;
    cout << "size of rotated area : " << rotatedarea << endl;
    cout << contourArea(contours[main_box])  << endl;
    cout << "size of rotated area percentage: " << contourArea(contours[main_box]) * (100.0 / rotatedarea)<< endl;
    cout << hierachy_size << " " << endl;
    cout << "move to x : " << 250 - rotated_rect.center.x << " and y : " << rotated_rect.center.y - 250 << endl; //use to determine how much the arm needs to rotate?
   
    imshow("img", img);
    //imshow("cropped", cropped_image);
}

Mat opencv::blur_difference(Mat img, int h1, int s1, int h2, int s2)
{
    Mat b1, b2, dif;
    GaussianBlur(img, b1, Size(h1, h1), s1);
    GaussianBlur(img, b2, Size(h2, h2), s2);

    dif = b1 - b2;

    return dif;
}

float opencv::area_percentage(vector<Point> contour)
{
    Rect rect = boundingRect(contour);
    int rectarea = rect.width * rect.height;
    return contourArea(contour) * (100.0 / rectarea);
}

float opencv::area_rotated_percentage(vector<Point> contour)
{
    RotatedRect rotated_rect = minAreaRect(contour);
    int rotatedarea = rotated_rect.size.width * rotated_rect.size.height;
    return contourArea(contour) * (100.0 / rotatedarea);;
}



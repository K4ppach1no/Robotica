#include "pch.h"
#include "opencv.h"

void opencv::detect_object(Mat img)
{
    RNG rng(12345);
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    Mat grey, thr;

    cvtColor(img, grey, COLOR_BGR2GRAY);

    threshold(blur_difference(grey, 7, 7, 17, 13), thr, 1, 255, THRESH_BINARY);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    int hierachy_size = 0;
    int main_box;
    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

    for (size_t i = 0; i < contours.size(); i++)
    {
        //drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        if (contourArea(contours[i]) > 1500 && hierarchy[i][3] == -1) {//
            int a = 0;
            for (int y = 0; y < hierarchy.size(); y++) {
                if (hierarchy[y][3] == i) {
                    a++;
                }
            }
            if (a > hierachy_size) {
                hierachy_size = a;
                main_box = i;
            }
        }
    }


    Rect rect = boundingRect(contours[main_box]);
    Point point1 = Point(rect.x + 0.5 * rect.width, rect.y + 0.5 * rect.height);

    circle(img, point1, 2, color, FILLED, LINE_8);
    rectangle(img, rect.tl(), rect.br(), color, 2);

    cout << point1 << " " << endl;
    cout << hierachy_size << " " << endl;
    cout << "move to x : "<< 250 - point1.x <<" and y : "<< point1.y-250 << endl; //use to determine how much the arm needs to rotate?



    imshow("img", img);
}

Mat opencv::blur_difference(Mat img, int h1, int s1, int h2, int s2)
{
    Mat b1, b2, dif;
    GaussianBlur(img, b1, Size(h1, h1), s1);
    GaussianBlur(img, b2, Size(h2, h2), s2);

    dif = b1 - b2;

    return dif;
}

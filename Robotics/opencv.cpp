#include "pch.h"
#include "opencv.h"

void opencv::detect_object()
{
    RNG rng(12345);
    string img_path = R"(C:\Users\Alissa\Documents\Stenden\robotica\testcases-photo\IMG_20230515_091527.jpg)"; //TODO: delete bard picture
    Mat img = imread(img_path, IMREAD_COLOR);
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    Mat grey, b1, b2, dif, thr;
    int h1 = 7, s1 = 7, h2 = 17, s2 = 13;

    cvtColor(img, grey, COLOR_BGR2GRAY);

    GaussianBlur(grey, b1, Size(h1, h1), s1);
    GaussianBlur(grey, b2, Size(h2, h2), s2);

    dif = b1 - b2;
    threshold(dif, thr, 1, 255, THRESH_BINARY);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(thr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    int hierachy_size = 0;
    int main_box;

    Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    for (size_t i = 0; i < contours.size(); i++)
    {
        //drawContours(img, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
        if (contourArea(contours[i]) > 1500 && hierarchy[i][3] == -1) {
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
    cout << hierachy_size << " " << endl;
    Rect rect = boundingRect(contours[main_box]);
    rectangle(img, rect.tl(), rect.br(), color, 2);

    //imshow("b1", b1);
    //imshow("b2", b2);
    //imshow("grey", grey);
    //imshow("dif", dif);
    imshow("thresh", thr);
    imshow("img", img);
}

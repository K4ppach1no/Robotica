#include "pch.h"

#include "controller.h"


void controller::remote_to_arm(int value)
{
}

void controller::weight_to_text(float weight)
{
}

void controller::led_aan(frequency frequence)
{
}

void controller::detect_object()
{
}

int main()
{
    string img_path = R"(..\bard.png)"; //TODO: delete bard picture
    Mat img = imread(img_path, IMREAD_COLOR);
    resize(img, img, { 500, 500 }, 0, 0, INTER_NEAREST);
    imshow("img", img);
    waitKey(0);
    cout << "Hello World!\n";
}
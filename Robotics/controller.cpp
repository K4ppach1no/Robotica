//#include "pch.h"
#include "controller.h"


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
    opencv opencv_;
    camera camera_;
    Mat img;

    while(true)
    {
        camera_.get_image_from_camera(img);

        if (img.empty()) {
            cerr << "ERROR! blank img grabbed\n";
            continue;
        }

        opencv_.detect_object(img);
        //imagedata.command_line();

        if (waitKey(5) >= 0)
            break;
    }

}
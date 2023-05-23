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

void camera() {
    opencv opencv_;
    //opencv_.detect_object();
    Mat frame, gray, boxed;
    VideoCapture cap = VideoCapture(0);
    cap.read(frame);

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        //cvtColor(frame, gray, COLOR_BGR2GRAY);
        // show live and wait for a key with timeout long enough to show images
        opencv_.detect_object(frame);
        //imshow("Live", gray);
        if (waitKey(5) >= 0)
            break;
    }
    cap.release();
}

int main()
{
    opencv opencv_;
    //string img_path = R"(C:\Users\Alissa\Documents\Stenden\robotica\testcases-photo\IMG_20230515_091455.jpg)"; //TODO: delete bard picture
    //Mat img = imread(img_path, IMREAD_COLOR);
    //opencv_.detect_object(img);
    //waitKey(0);
    camera();
}
#include "pch.h"


#include "camera.h"

#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


camera::camera() {
 cap = cv::VideoCapture(0);
 cout << "camera instanciated";
}

camera::~camera() {
	cap.release();
    cout << "camera destructured";
}

void camera::make_video()
{
}

void camera::get_image_from_camera(Mat &img)
{
    // wait for a new frame from camera and store it into 'frame'
    cap.read(img);
    // check if we succeeded

}


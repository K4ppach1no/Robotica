#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "controller.h"
#include "opencv.h"

#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


class camera
{
private:
	//controller controller;
	//opencv opencv;
	cv::VideoCapture cap;

public:
	camera();
	~camera();
	void make_video();

	void get_image_from_camera(cv::Mat &img);
};
#endif

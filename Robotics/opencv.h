#ifndef OPENCV_H
#define OPENCV_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>


#include "camera.h"
#include "controller.h"
#include "website.h"
#include "grab_arm.h"
#include "track_motor.h"
#include "medicine_box.h"
#include "image_data.h"

class opencv
{
private:
	//camera camera;
	//class controller controller;
	//website website;
	//grab_arm grab_arm;
	//track_motor track_motor;
	//medicine_box medicine_box[];

public:
	void detect_object(Mat img);

	Mat blur_difference(Mat img, int h1, int s1, int h2, int s2);

	float area_rotated_percentage(vector<Point> contour);

};
#endif

#pragma once


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

class image_data
{
private:
	Point2f center;
	float angle;
	double contourarea, contourpercentage;
	int rotatedarea, kids, movex, movey;

public:
	image_data();
	image_data(Point2f center_,
		float angle_,
		double contourarea_, double contourpercentage_,
		int rotatedarea_, int kids_, int movex_, int movey_);
	void command_line();
};


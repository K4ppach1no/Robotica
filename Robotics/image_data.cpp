#include "image_data.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cassert>

#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

image_data::image_data()
{
}

image_data::image_data(Point2f center_, float angle_, double contourarea_, double contourpercentage_, int rotatedarea_, int kids_, int movex_, int movey_)
{
	center = center_;
	angle = angle_;
	contourarea = contourarea_;
	contourpercentage = contourpercentage_;
	rotatedarea = rotatedarea_;
	kids = kids_;
	movex = movex_;
	movey = movey_;

}

void image_data::command_line()
{
	// Print information about the main object
	cout << center << endl;
	cout << angle << endl;
	cout << "size of rotated area: " << rotatedarea << endl;
	cout << contourarea << endl;
	cout << "size of rotated area percentage: " << contourarea << endl;
	cout << kids << " " << endl;
	cout << "move to x: " << movex << " and y: " << movey << endl;
}

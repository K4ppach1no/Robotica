#ifndef MEDICINE_BOX_H
#define MEDICINE_BOX_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "weight_sensor.h"
#include "website.h"
#include "speaker.h"
#include "opencv.h"

class medicine_box
{
private:
	float Weight;

	int code ;

	//weight_sensor weight_sensor;
	//website website;
	//speaker speaker;
	//opencv opencv;

public:
	string weight_to_string();

};
#endif

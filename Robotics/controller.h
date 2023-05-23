#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "grab_arm.h"
#include "remote_controler.h"
#include "track_motor.h"
#include "microphone.h"
#include "parser.h"
#include "website.h"
#include "camera.h"
#include "weight_sensor.h"
#include "led.h"
#include "accelerator.h"
#include "speaker.h"
#include "opencv.h"
#include "frequence.h"

class controller
{
private:
	//grab_arm grab_arm;
	//remote_controler remote_controler;
	//track_motor track_motor;
	//microphone microphone;
	//parser parser;
	//website website;
	//camera camera;
	//weight_sensor weight_sensor;
	//led led[];
	//accelerator accelerator;
	//speaker speaker;
	//class opencv opencv_;
	//frequence frequences[];

public:
	void remote_to_arm(int value);

	void weight_to_text(float weight);

	void led_aan(frequency frequence);

	void detect_object();

};
#endif

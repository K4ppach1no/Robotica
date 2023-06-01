#pragma once
#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <chrono>
#include <thread>


class bluetooth
{
public:
	void connect();
	static void on_device_found();
	static void on_property_changed();
};


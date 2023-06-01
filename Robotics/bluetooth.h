#pragma once
#include <sdbus-c++/sdbus-c++.h>
#include <iostream>

class bluetooth
{
public:
	void connect();
};

void onsignal_callback();

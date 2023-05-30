#ifndef REMOTE_CONTROLER_H
#define REMOTE_CONTROLER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "controller.h"
#include "parser.h"

using namespace std;
class remote_controler
{
private:
	//controller controller;
	//parser parser;

public:
	int open_arm();

	void move_foward();

	void move_left();

	void move_right();

	void move_backward();

	string receive_signal();

};
#endif

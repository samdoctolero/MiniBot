#pragma once
#include "Laser.h"
#include "Navigation.h"


class Robot
{
public:
	Robot();
	~Robot();
	Navigation nav;
	Laser laser;
	void run();
};


#pragma once
#include <iostream>
#include <chrono>
#include "Point.h"
#include "Line.h"
#define _USE_MATH_DEFINES

class Tester
{
public:
	Tester();
	~Tester();
	void testAll();
	bool testProjectionTrvial();
	bool testPointsToLineTrivial();
};


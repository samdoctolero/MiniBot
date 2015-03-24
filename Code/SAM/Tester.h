#pragma once
#include <iostream>
#include <chrono>
#include "Point.h"
#include "Line.h"
#include "PointLine.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Tester
{
public:
	Tester();
	~Tester();
	void testAll();
	bool testProjectionTrvial();
	bool testPointsToLineTrivial();
	bool testLineAngleTrivial();
	bool testPointLineAngleTirvial();
	bool testPointLineAngle90();
	bool testPointLineAngle45();
	bool testPointDistance();

};


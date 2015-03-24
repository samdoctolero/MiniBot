#pragma once
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class Point
{	
public:
	double x;
	double y;
	double slope(Point other);
	Point(double x, double y);
	Point();
	~Point();
	double distance(Point other);
	bool operator==(Point other);
	string toString();
};


#pragma once
#include <string>
#include <sstream>

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
	bool operator==(Point other);
	string toString();
};


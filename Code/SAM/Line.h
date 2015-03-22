#pragma once
#include "Point.h"
#include <vector>
#include <gsl/gsl_fit.h>
#include <sstream>

using namespace std;
//test

class Line
{
private:
	
public:
	Line();
	~Line();
	Line(double r, double theta);
	double r, theta; //for the eqn r = x cos(theta) + y sin(theta)
	double distance(Point other);
	Point project(Point other);
	static Line pointsToLine(vector<Point> P, int startIndex, int endIndex);
	bool operator==(Line other);
	string toString();
};


#pragma once
#include "Point.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
//test

class Line
{
private:
	
public:
	Line();
	~Line();
	Line(double m, double b);
	double m, b; //for the eqn y = mx + b
	double distance(Point other);
	Point project(Point other);
	bool sameSide(Point p1, Point p2);
	static Line totalLeastSquares();
	static Line pointsToLine(vector<Point> P, int startIndex, int endIndex);
	bool operator==(Line other);
	double angle(Line other);
	string toString();
};


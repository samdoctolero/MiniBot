#include "Point.h"


Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point::Point()
{
}

double Point::slope(Point other)
{
	return (y - other.y) / (x - other.x);
}

Point::~Point()
{

}

double Point::distance(Point other)
{
	double x1 = x - other.x;
	double y1 = y - other.y;
	return sqrt(x1*x1 + y1*y1);
}

bool Point::operator==(Point other)
{
	return x == other.x && y == other.y;
}

string Point::toString()
{
	stringstream ss;
	//ss << "(" << x << "," << y << ")";
	ss << x << "\t" << y;
	return ss.str();
}

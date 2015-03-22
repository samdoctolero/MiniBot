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

bool Point::operator==(Point other)
{
	return x == other.x && y == other.y;
}

string Point::toString()
{
	stringstream ss;
	ss << "(" << x << "," << y << ")";
	return ss.str();
}

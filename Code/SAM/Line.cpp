#include "Line.h"


Line::Line()
{
}


Line::~Line()
{
}

Line::Line(double r, double theta)
{
	this->r = r;
	this->theta = theta;
}

double Line::distance(Point other)
{
	
}


Line Line::pointsToLine(vector<Point> P, int startIndex, int endIndex)
{
	double* x = new double[P.size()];
	double* y = new double[P.size()];

	for (int i = startIndex; i < endIndex; i++)
	{
		x[i] = P[i].x;
		y[i] = P[i].y;
	}

	double c0, c1, cov00, cov01, cov11, sumsq;

	gsl_fit_linear(x, 1, y, 1, endIndex-startIndex, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);

	double b = c0;
	double m = c1;

	Line l;
	l.r = b/2*sqrt((1+m*m)/(m*m));
	l.theta = atan(-m);
	return l;
}

constexpr double pi() { return atan(1) * 4; }//computed at compile time
Point Line::project(Point other)
{
	//rp, theta + pi/2 = new line that is perp to original going through other
	double rp = other.x*cos(theta + (pi() / 2.0)) + other.y*sin(theta + (pi() / 2.0));
	double numer = r + (rp*sin(theta)) / sin(theta + pi() / 2);
	double denom = cos(theta) + (cos(theta + pi() / 2)*sin(theta)) / sin(theta + pi() / 2);
	double newX = numer / denom;
	double newY = (newX*cos(theta) / sin(theta)) - r;

	return Point(newX, newY);
}

bool Line::operator==(Line other)
{
	return r == other.r && theta == other.theta;
}

string Line::toString()
{
	stringstream ss;
	ss << "(" << r << "," << theta << ")";
	return ss.str();
}
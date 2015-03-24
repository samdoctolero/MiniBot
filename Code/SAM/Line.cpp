#include "Line.h"
#include "PointLine.h"

Line::Line()
{
}


Line::~Line()
{
}

double Line::distance(Point other)
{
	Point p = project(other);
	return p.distance(other);
}

Point Line::project(Point other)
{
	double d = (other.x + (other.y - b)*m) / (1 + m*m);
	double x = 2 * d - other.x;
	double y = 2 * d*m - other.y + 2 * b;
	return Point(x, y);
}

double Line::angle(Line other)
{
	return atan((m - other.m) / (1 + m*other.m));
}

Line Line::pointsToLine(vector<Point> P, int startIndex, int endIndex)
{
	/*PointLine p;
	p.start = P[startIndex];
	p.end = P[endIndex];
	return p.toLine();*/

	//based on http://en.wikipedia.org/wiki/Deming_regression

	double xavg = 0;
	double yavg = 0;
	double sig = 1;
	double n = P.size();

	for (auto it = P.begin(); it < P.end(); it++)
	{
		xavg += (*it).x;
		yavg += (*it).y;
	}
	
	xavg /= n;
	yavg /= n;

	double sxx = 0;
	double syy = 0;
	double sxy = 0;
	for (auto it = P.begin(); it < P.end(); it++)
	{
		sxx += pow(((*it).x - xavg),2);
		sxy += ((*it).x - xavg)*((*it).y - yavg);
		syy += pow(((*it).y - yavg),2);
	}
	
	sxx /= (n-1);
	sxy /= (n-1);
	syy /= (n-1);

	double beta1 = (syy - sig*sxx + sqrt(pow((syy - sig*sxx),2) + 4 * sig * sxy * sxy)) / (2 * sxy);
	double beta0 = yavg - beta1*xavg;

	Line l;
	l.m = beta1;
	l.b = beta0;
	return l;

	/*Row<double> x(P.size());
	Row<double> y(P.size());

	for (int i = startIndex; i < endIndex; i++)
	{
		x << P[i].x;
		y << P[i].y;
	}
	
	int m = P.size();
	int n = x.n_cols;
	
	mat Z = join_rows(x, y);

	mat U;
	vec s;
	mat V;

	svd(U, s, V, Z);
	
	mat VXY = V(span(0, (n-1)), span(n, (V.n_cols-1)));
	mat VYY = V(span(n, (V.n_rows-1)) , span(n, (V.n_cols-1)));

	mat B = (-1*VXY) / VYY;

	cout << B << endl;
	cout << "press enter to continue";
	cin.get();

	//old method
	//double c0, c1, cov00, cov01, cov11, sumsq;
	//gsl_fit_linear(x, 1, y, 1, endIndex - startIndex, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);
	
	Line l;
	

	//l.b = c0;
	//l.m = c1;
	return l;*/
}



bool Line::operator==(Line other)
{
	return m == other.m && b == other.b;
}

bool Line::sameSide(Point p1, Point p2)
{
	//get two random points
	double x1 = 10.0;
	double y1 = m * x1 + b;

	double x2 = -10;
	double y2 = m * x2 + b;
	
	//eqn from http://math.stackexchange.com/questions/162728/how-to-determine-if-2-points-are-on-opposite-sides-of-a-line
	double left = (y1 - y2)*(p1.x - x1) + (x2 - x1)*(p1.y - y1);
	double right = (y1 - y2)*(p2.x - x1) + (x2 - x1)*(p2.y - y1);

	return 0 < left*right;
}

string Line::toString()
{
	stringstream ss;
	ss << "y = " << m << " * x + " << b;
	return ss.str();
}


/*
Line::Line(double r, double theta)
{
	this->r = r;
	this->theta = theta;
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
*/
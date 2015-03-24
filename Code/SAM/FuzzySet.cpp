#include "FuzzySet.h"


FuzzySet::FuzzySet()
{
}


FuzzySet::~FuzzySet()
{
}

double FuzzySet::degreeOfMem(double value)
{
	int i = 0;
	while (i < points.size() - 1 && !(points[i].x <= value && points[i + 1].x >= value))
		i++;
	if (i >= points.size() - 1)
		return 0;
	double y1 = points[i].y;
	double y2 = points[i + 1].y;
	double x1 = points[i].x;
	double x2 = points[i + 1].x;

	return ((y1 - y2) / (x1 - x2))*(value - x1) + y1;
}
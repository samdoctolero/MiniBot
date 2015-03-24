#pragma once
#include "Point.h"
#include <vector>

using namespace std;

class FuzzySet
{
public:
	vector<Point> points;
	FuzzySet();
	~FuzzySet();
	double degreeOfMem(double input);
};


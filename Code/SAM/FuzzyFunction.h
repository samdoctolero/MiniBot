#pragma once
#include <vector>
#include "Point.h"
#include "FuzzySet.h"
#include <iostream>
using namespace std;

class FuzzyFunction
{
public:
	vector<FuzzySet> inputFunction;
	vector<double> outputFunction;
	double getCripsOutput(double value);
	FuzzyFunction();
	~FuzzyFunction();
};


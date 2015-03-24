#pragma once
#include "FuzzyFunction.h"
#include "Point.h"

class State
{
public:
	FuzzyFunction function;
	Point target;
	State();
	~State();
};


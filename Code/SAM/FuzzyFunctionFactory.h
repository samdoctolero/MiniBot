#pragma once
#include "FuzzyFunction.h"
#include <limits>

class FuzzyFunctionFactory
{
public:
	FuzzyFunctionFactory();
	~FuzzyFunctionFactory();
	static FuzzyFunction getGoalSeakingFunction();
	static FuzzyFunction getObjectOrientFunction();
	static FuzzyFunction getReverseFunction();
	static FuzzyFunction getReverseTurnFunction();
	static FuzzyFunction getAdjustFunction();
};


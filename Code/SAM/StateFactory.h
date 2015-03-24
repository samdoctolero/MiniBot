#pragma once
#include "State.h"
#include "Point.h"
#include "FuzzyFunctionFactory.h"
#include "Constants.h"

class StateFactory
{
public:
	StateFactory();
	~StateFactory();
	static State getGoalSeakingState();
	static State getObjectOrientState();
	static State getReverseState();
	static State getReverseTurnState();
	static State getAdjustState();
};

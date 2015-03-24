#include "StateFactory.h"

StateFactory::StateFactory()
{

}

StateFactory::~StateFactory()
{

}

State StateFactory::getGoalSeakingState()
{
	Point target(Constants::robotLength*0.5 + Constants::gapLength, Constants::carWidth + 0.65*Constants::robotWidth);
	FuzzyFunction ff = FuzzyFunctionFactory::getGoalSeakingFunction();
	State s;
	s.function = ff;
	s.target = target;
	return s;
}

State StateFactory::getObjectOrientState()
{
	State s;
	return s;
}


State StateFactory::getReverseState()
{
	State s;
	return s;
}

State StateFactory::getReverseTurnState()
{
	State s;
	return s;
}

State StateFactory::getAdjustState()
{
	State s;
	return s;
}

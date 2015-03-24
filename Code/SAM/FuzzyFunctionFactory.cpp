#include "FuzzyFunctionFactory.h"


FuzzyFunctionFactory::FuzzyFunctionFactory()
{
}


FuzzyFunctionFactory::~FuzzyFunctionFactory()
{
}

FuzzyFunction FuzzyFunctionFactory::getGoalSeakingFunction()
{
	FuzzyFunction ff;

	FuzzySet N;
	N.points.push_back(Point(numeric_limits<double>::min(), 1));
	N.points.push_back(Point(-3, 1));
	N.points.push_back(Point(0, 0));
	ff.inputFunction.push_back(N);

	FuzzySet Z;
	Z.points.push_back(Point(-3, 0));
	Z.points.push_back(Point(0, 1));
	Z.points.push_back(Point(3, 0));
	ff.inputFunction.push_back(Z);

	FuzzySet P;
	P.points.push_back(Point(0, 0));
	P.points.push_back(Point(3, 1));
	P.points.push_back(Point(numeric_limits<double>::max(), 1));
	ff.inputFunction.push_back(P);

	double NOutPeak = -1;
	double ZOutPeak = 0;
	double POutPeak = 1;
	//order matters!!!!!!!
	ff.outputFunction.push_back(POutPeak);
	ff.outputFunction.push_back(ZOutPeak);
	ff.outputFunction.push_back(NOutPeak);

	return ff;
}

FuzzyFunction FuzzyFunctionFactory::getObjectOrientFunction()
{
	FuzzyFunction ff;

	FuzzySet NBInput;
	NBInput.points.push_back(Point(-1,0));
	NBInput.points.push_back(Point(-1, 1));
	NBInput.points.push_back(Point(-0.5, 0));
	ff.inputFunction.push_back(NBInput);

	FuzzySet NMInput;
	NMInput.points.push_back(Point(-0.65, 0));
	NMInput.points.push_back(Point(-0.325, 1));
	NMInput.points.push_back(Point(0, 0));
	ff.inputFunction.push_back(NMInput);

	FuzzySet ZInput;
	ZInput.points.push_back(Point(-0.15, 0));
	ZInput.points.push_back(Point(0, 1));
	ZInput.points.push_back(Point(0.15, 0));
	ff.inputFunction.push_back(ZInput);

	FuzzySet PMInput;
	PMInput.points.push_back(Point(0, 0));
	PMInput.points.push_back(Point(0.325, 1));
	PMInput.points.push_back(Point(0.65, 0));
	ff.inputFunction.push_back(PMInput);
	return ff;
}

FuzzyFunction FuzzyFunctionFactory::getReverseFunction()
{
	FuzzyFunction ff;
	return ff;
}

FuzzyFunction FuzzyFunctionFactory::getReverseTurnFunction()
{
	FuzzyFunction ff;
	return ff;
}

FuzzyFunction FuzzyFunctionFactory::getAdjustFunction()
{
	FuzzyFunction ff;
	return ff;
}

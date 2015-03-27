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
	NBInput.points.push_back(Point(-1.7,0));
	NBInput.points.push_back(Point(-1.5, 1));
	NBInput.points.push_back(Point(-0.75, 0));
	ff.inputFunction.push_back(NBInput);

	FuzzySet NMInput;
	NMInput.points.push_back(Point(-1.1, 0));
	NMInput.points.push_back(Point(-0.5, 1));
	NMInput.points.push_back(Point(0, 0));
	ff.inputFunction.push_back(NMInput);

	FuzzySet ZInput;
	ZInput.points.push_back(Point(-0.4,0));
	ZInput.points.push_back(Point(0, 1));
	ZInput.points.push_back(Point(0.4,0 ));
	ff.inputFunction.push_back(ZInput);

	FuzzySet PMInput;
	PMInput.points.push_back(Point(0, 0));
	PMInput.points.push_back(Point(0.5, 1));
	PMInput.points.push_back(Point(1.1, 0));
	ff.inputFunction.push_back(PMInput);
	
	FuzzySet PBInput;
	PBInput.points.push_back(Point(0.75, 0));
	PBInput.points.push_back(Point(1.5, 1));
	PBInput.points.push_back(Point(1.6, 0));
	ff.inputFunction.push_back(PBInput);

	ff.inputFunction.push_back(PBOutPeak);
	ff.inputFunction.push_back(PMOutPeak);
	ff.inputFunction.push_back(ZOutPeak);
	ff.inputFunction.push_back(NMOutPeak);
	ff.inputFunction.push_back(NBOutPeak);

	return ff;
}

FuzzyFunction FuzzyFunctionFactory::getReverseFunction()
{
	FuzzyFunction ff;

	FuzzySet Sinput;
	Sinput.points.push_back(Point(0, 0));
	Sinput.points.push_back(Point(0, 1));
	Sinput.points.push_back(Point(0.25, 0));
	ff.inputFunction.push_back(S);

	FuzzySet Binput;
	Binput.points.push_back(Point(0, 0));
	Binput.points.push_back(Point(0.25, 1));
	Binput.points.push_back(Point(0.9, 0));
	ff.inputFunction.push_back(B);

	FuzzySet VBinput;
	VBinput.points.push_back(Point(0.4, 0));
	VBinput.points.push_back(Point(1, 1));
	VBinput.points.push_back(Point(2, 1));
	VBinput.points.push_back(Point(2, 0));
	ff.inputFunction.push_back(VB);

	ff.outputFunction.push_back(ZOutPeak);
	ff.outputFunction.push_back(NMOutPeak);
	ff.outputFunction.push_back(NBOutPeak);


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

#include "FuzzyFunction.h"


FuzzyFunction::FuzzyFunction()
{

}


FuzzyFunction::~FuzzyFunction()
{

}

double FuzzyFunction::getCripsOutput(double value)
{
	if (inputFunction.size() != outputFunction.size())
	{
		cout << "Input fuzzy function does not match output function" << endl;
		throw "Input fuzzy function does not match output function";
	}
	
	double componentTotal = 0;

	for (int i = 0; i < inputFunction.size(); i++)
	{
		componentTotal += inputFunction[i].degreeOfMem(value) * outputFunction[i];
	}
	return componentTotal;
}


//#include <SerialStream.h>
#include <iostream>
#include "Robot.h"
#include "Tester.h"
#include "Constants.h"
#define _USE_MATH_DEFINES

using namespace std;
//using namespace LibSerial;

int main(int argv, char** argc)
{
	//cout << "starting" << endl;
	if (argv != 1)
	{
		cout << "entering test mode" << endl;
		Tester t;
		t.testAll();
		return 1;
	}
	Robot r;
	try
	{
		//cout << "running" << endl;
		r.run();
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	
	return 1;
}
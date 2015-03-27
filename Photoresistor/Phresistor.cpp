
#include <iostream>
#include <stdlib.h>
#include "Sensors.h"

using namespace std;

int main()
{
	Sensors test;
	
	test.WaitForLight();

	cout << "Light detected.\nExiting..." << endl;
	return 0;
}


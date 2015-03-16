#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>

#define PHREST 6

using namespace std;

int main()
{
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup faied..." << endl;
		exit(1);
	}
	
	pinMode(PHREST, INPUT);
	int read = 0;
	while (read == 0)
	{
		//if key pressed then exit

		read = digitalRead(PHREST);	
		delay(1);
	}

	cout << "Pin low" << endl;
	return 0;
}


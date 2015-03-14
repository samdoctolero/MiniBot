#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>

//Figure out pin numbering on B+
#define LEFT 4 //BCM GPIO 23
#define RIGHT 5//BCM GPIO 24
#define TPAUSE 2 //Change this for the time it takes to pause
using namespace std;

int main()
{
	if (wiringPiSetup() == -1)
	{
		exit(1);
	}

	//I believe it's soft pwm but i an not sure
	pinMode(0, PWM_TONE_OUTPUT);
	//pinMode(RIGHT, PWM_OUTPUT);

	//for (int i = 0; i <= 20; i++)
	//pwmWrite(LEFT, 520);

	cout << "Starting" << endl;
	while (true)
	{
		//int val;
		//cout << "Enter value:" << endl;
		//cin >> val;
		//If this works the same way as Parallax
		//Then 512 will be the neutral zone 
		//Higher or lower than that will make it go CCW or CW//
		pwmWrite(1, 500);
		//Adjust potentiometer to get no movement on the servos
		delay(TPAUSE);
		//cout << "Pause" << endl;
	}
	return 0;
}
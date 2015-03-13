#include "WiringPi\wiringPi.h"
#include <stdlib.h>

//Figure out pin numbering on B+
#define LEFT 1 //GPIO 18
#define RIGHT 2//Change this
#define TPAUSE 1 //Change this for the time it takes to pause
using namespace std;

void main()
{
	if (wiringPiSetup() == -1)
	{
		exit(1);
	}

	//I believe it's soft pwm but i an not sure
	pinMode(LEFT, SOFT_PWM_OUTPUT);
	pinMode(RIGHT, SOFT_PWM_OUTPUT);

	//for (int i = 0; i <= 20; i++)
	while (true)
	{
		//If this works the same way as Parallax
		//Then 512 will be the neutral zone 
		//Higher or lower than that will make it go CCW or CW
		pwmWrite(LEFT, 512);
		pwmWrite(RIGHT, 512);
		//Adjust potentiometer to get no movement on the servos
		delay(TPAUSE);
	}

}
#include "ServoController.h"
#include <iomanip>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <stdexcept>


int main()
{
	ServoController Servo;
	Servo.BasicCMD(ServoController::START);
	Servo.BasicCMD(ServoController::FORWARD);

	for (int i = -40; i < 40;i=i+5)
	{
		cout << "Heading: " << i<<endl;
		Servo.AdjustHeading(i);
		usleep(500000);
		
	}
	Servo.BasicCMD(ServoController::STOP);
	return 0;
}
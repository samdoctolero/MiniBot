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

	for (int i = 10; i >- 10;i=i-1)
	{
		cout << "Heading: " << i<<endl;
		Servo.AdjustHeading(i);
		usleep(500000);
		
	}
	Servo.BasicCMD(ServoController::STOP);
	return 0;
}
#include "Bot.h"
#include <softServo.h>
#include <iostream>
#include <wiringPi.h> //make sure to use -lwiringPi at the end of the compile command
#include <stdlib.h>

Servos::Bot()
{
	//wiringPi setup by Gordon. Maps and accesses gpios
	//Initialize wiringPi
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup faied..." << endl;
		exit(1); //If setup fails then exit the main program
	}

	//initalize servo PWM 
	softServoSetup(LEFT_SERVO, RIGHT_SERVO, -1, -1, -1, -1, -1, -1);
	LoopContinue - 1;
}


Servos::~Bot()
{
}

Servos::GetLoopContinue()
{
	this->LoopContinue;
}

Servo::SetLoopContinue()
{
	this->LoopContinue = 0;
}

/*
Main program loop
*/
void Begin()
{
	while (LoopContinue == 1)
	{
		//Scan


		//Process


		//Move -- Probably make a thread while moving to scan while moving

	}
	
}


/*
Rotate the wheels at certain speeds
*/
void MoveWheels(int LeftVal, int RightVal, int count)
{
	//value1 and value2 should always be between -250 and 1250. 
	//even if they are outside the boundaries the softServo class takes that into account
	//if value < -250 then value = -250
	//if value > 1250 then value = 1250
	//Midpoint = 500; both wheels should be stopped

	//Left wheel will follow the rotation of the right wheel
	LeftVal = -LeftVal + 1000; //Take into account that the wheels rotate in opposite directions

	for (int i = 0; i <= count; i++)
	{
		softServoWrite(RIGHT_SERVO, RightVal);
		softServoWrite(LEFT_SERVO, LeftVal);
		delay(10); //10ms
	}
}

/*
Loops continuously until the photoresistor senses enough light.
*/
void WaitForLight()
{
	pinMode(PHOTO_RES, INPUT);
	int read = 0;
	while (read == 0)
	{
		read = digitalRead(PHOTO_RES);
		delay(1); //rests for 1ms

		//This section is probably not needed
		//Included just in case the pin does not read a proper HIGH or LOW
		if (read != 0 or read != 1)
		{
			read = 0;
		}
	}
}

//Returns the distance measurement from the back left sensor
int BackLeftDistance()
{

}

//Returns the distance measurement from the back right sensor
int BackRightDistance()
{

}

//Returns the distance measurement straight from the back
int BackDistance()
{


}
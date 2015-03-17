#include "Bot.h"
#include <softServo.h>
#include <iostream>
#include <wiringPi.h> //make sure to use -lwiringPi at the end of the compile command
#include <stdlib.h>

Bot::Bot()
{
	//wiringPi setup by Gordon. Maps and accesses gpios
	//Initialize wiringPi
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup faied..." << endl;
		exit(1); //If setup fails then exit the main program
	}

	//Initalize servo PWM 
	softServoSetup(LEFT_SERVO, RIGHT_SERVO, -1, -1, -1, -1, -1, -1);

	//Put values in variables
	this->LoopContinue - 1;

}


Bot::~Bot()
{
}

//Getters and setters implementation
int Bot::GetLoopContinue(){this->LoopContinue;}
void Bot::SetLoopContinue(int val){this->LoopContinue = val;}

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
void MoveWheels(int LeftSpeed, int RightSpeed, int count)
{
	//value1 and value2 should always be between -250 and 1250. 
	//even if they are outside the boundaries the softServo class takes that into account
	//if value < -250 then value = -250
	//if value > 1250 then value = 1250
	//Midpoint = 500; both wheels should be stopped

	//Left wheel will follow the rotation of the right wheel
	LeftSpeed = -LeftSpeed + 1000; //Take into account that the wheels rotate in opposite directions

	//count could either be distance or time (don't know how we are going to use it yet...)
	for (int i = 0; i <= count; i++)
	{
		softServoWrite(RIGHT_SERVO, RightSpeed);
		softServoWrite(LEFT_SERVO, LeftSpeed);
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
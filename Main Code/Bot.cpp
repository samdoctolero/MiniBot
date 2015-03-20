#include "Bot.h"
#include <softServo.h>
#include <iostream>
#include <wiringPi.h> //make sure to use -lwiringPi at the end of the compile command
#include <stdlib.h>

using namespace std;

Bot::Bot()
{
	//wiringPi setup by Gordon. Maps and accesses gpios
	//Initialize wiringPi
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup faied..." << endl;
		exit(1); //If setup fails then exit the main program
	}

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
void Bot::Begin()
{
	while (LoopContinue == 1)
	{
		//Scan


		//Process


		//Move -- Probably make a thread while moving to scan while moving

	}
	
}

/*
Loops continuously until the photoresistor senses enough light.
*/
void Bot::WaitForLight()
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
int Bot::BackLeftDistance()
{

}

//Returns the distance measurement from the back right sensor
int Bot::BackRightDistance()
{

}

//Returns the distance measurement straight from the back using PING
int Bot::BackDistance()
{
	int numScans = 5;

	double cumDistance = 0;
	for (int i = 0; i < numScans; i++)
	{
		pinMode(PING, OUTPUT);
		digitalWrite(PING, 0); //Reset to zero
		delay(2);
		//Start of transmission
		digitalWrite(PING, 1);
		delayMicroseconds(5);
		digitalWrite(PING, 0);
		//Activated PING to scan
		//Change pin mode to accept signals
		pinMode(PING, INPUT);

		delayMicroseconds(750);
		//once the signal is high then measure how long it stays high;
		double utime = 0;
		while (digitalRead(PING) == 1)
		{
			delayMicroseconds(8);
			utime += 8;
		}
		cumDistance += utime / 29 / 2;
		delayMicroseconds(200); //delay 200microseconds before next read
	}

	double distance = cumDistance / numScan; //average the findings to get the final result

	return distance;
}
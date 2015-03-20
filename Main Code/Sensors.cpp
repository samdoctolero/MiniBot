#include "Sensors.h"
#include <iostream>
#include <wiringPi.h> //make sure to use -lwiringPi at the end of the compile command
#include <stdlib.h>

using namespace std;


Sensor::Sensor() //Constructor
{
	wiringPisetup();
}
Sensor::~Sensor()//Destructor
{

}

double Sensor::GetPingDistance()//Grab the current distance from the class
{

}

void Sensor::PingScan()//Tell the sensor to scan and change the PingDistance variable
{

}

bool Sensor::GetLeftObjectPresent()
{

}

void Sensor::LeftIRScan()
{

}

bool Sensor::GetRightObjectPresent()
{

}

void Sensor::RightIRScan()
{

}



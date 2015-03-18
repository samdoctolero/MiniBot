/*
* servo.c:
*	Test of the softServo code.
*	Do not use this code - use the servoBlaster kernel module instead
*
* Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
***********************************************************************
* This file is part of wiringPi:
*	https://projects.drogon.net/raspberry-pi/wiringpi/
*
*    wiringPi is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Lesser General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    wiringPi is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Lesser General Public License for more details.
*
*    You should have received a copy of the GNU Lesser General Public License
*    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>

#include <wiringPi.h>
#include "softServo.h"

#define INCRMT 50
#define MAX 1500
#define MIN -250

#define LEFT 4
#define RIGHT 5

using namespace std;

void MoveWheels(int pin1, int pin2, int count);

int main()
{
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "oops: %s\n", strerror(errno));
		return 1;
	}

	softServoSetup(RIGHT, LEFT, -1, -1, -1, -1, -1, -1);

	int value = -250;

	while (value <= 1250)
	{
		cout << value << endl;
		MoveWheels(value, value, 50);
		value = value + INCRMT;

	}

	return 0;
}


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
		softServoWrite(RIGHT, RightSpeed);
		softServoWrite(LEFT, LeftSpeed);
		delay(10); //10ms
	}
}

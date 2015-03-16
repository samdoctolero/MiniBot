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

#define INCRMT 10
#define MAX 1500
#define MIN -250

#define LEFT 1
#define RIGHT 4

using namespace std;

int main()
{
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "oops: %s\n", strerror(errno));
		return 1;
	}

	softServoSetup(-1, RIGHT, -1, -1, -1, -1, -1, -1);


	int dutyCycle1 = -250;
	int dutyCycle2 = 1500;
	//while ((dutyCycle1 >= MIN) && (dutyCycle1 <= MAX))
	for (int t = 0; t < 300; t++)
	{
		//cout << "Value Left: " << dutyCycle1 << ", Value Right: "<< dutyCycle2 << endl;
		cout << t << endl;
		for (int i = 0; i < 10;i++)
		{ 
			//softServoWrite(LEFT, 750);
			softServoWrite(RIGHT, 750);

			delay(10); //10ms
		}
		dutyCycle1 = dutyCycle1 + INCRMT;
		dutyCycle2 = dutyCycle2 - INCRMT;
	}

	cout << "End of test..." << endl;
	return 0;
}

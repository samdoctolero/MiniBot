
#include "Wheels.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>

#include <wiringPi.h>
#include "softServo.h"

#define LEFT 4
#define RIGHT 5
#define RADIUS 6.8 //cm

using namespace std;

Wheels::Wheels()
{
	wiringPiSetup();
	softServoSetup(LEFT, RIGHT, -1, -1, -1, -1, -1, -1);
	MoveFlag = 1;
	leftSpeed = 0;
	rightSpeed = 0;
}

Wheels::~Wheels(){}

void Wheels::Move()
{
	while (MoveFlag == 1) //wheels will keep moving as long as this flag is true
	{
		softServoWrite(RIGHT, rightSpeed);
		softServoWrite(LEFT, leftSpeed);
		delay(10); //10ms
	}
}

void Wheels::GetSpeeds(int &left, int &right)
{
	left = leftSpeed;
	right = rightSpeed;
}

void Wheels::UpdateSpeeds(int left, int right)
{
	//Accepts -750 to 750: +ve go forward and -ve move back

	//Actual speed goes from -250 to 1250
	//Calculate the offset
	left = left + 250;
	right = right + 250;

	//Reverse left servo
	leftSpeed = -left + 1000;

	leftSpeed = left;
	rightSpeed = right;
}

void Wheels::UpdateFlag(int flag)
{
	MoveFlag = flag;
	if (flag == 0) //wheels should be stopped
	{
		UpdateSpeeds(0, 0);
	}
}

int Wheels::GetFlag()
{
	return MoveFlag;
}



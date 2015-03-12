/*
Servo.cpp
Contains functions and data types for controlling the wheels
Uses softPwm.c functions from WiringPi (Gordon Projects)
*/


#include "Servo.h"
#include "WiringPi\softPwm.h"
#include "WiringPi\wiringPi.h"

void Servo::SetPin(int PinNum)
{
	Pin = PinNum;
}

void Servo::SetRadius(int RadNum)
{
	Radius = RadNum;
}

Servo::Servo()
{
	wiringPiSetup();
	softPwmCreate(this->Pin, 0, 100);
}


Servo::~Servo()
{
}

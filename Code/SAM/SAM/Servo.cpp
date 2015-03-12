/*
Servo.cpp
Contains functions and data types for controlling the wheels
Uses softPwm.c functions from WiringPi (Gordon Projects)
*/


#include "Servo.h"
#include "softPwm.h"

#define WHEEL_RADIUS 26; //in CM (measure wheel radius)

//Define class global variables
struct Wheel
{
	int Pin;
};



int Travel(int distance) 
{
	//Figure out distance and duration of loop relationship 
	//softPwmWrite()
}


Servo::Servo()
{

}


Servo::~Servo()
{
}

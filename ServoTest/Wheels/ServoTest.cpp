/*
ServoTest.cpp
*/

#include <iostream>
//#include <thread>
//#include "Wheels.h
#include <wiringPi.h>
#include "softServo.h"

#define LEFT 4
#define RIGHT 5

using namespace std;
void UpdateSpeeds(int left, int right);
int main()
{
	//Wheels Servo;
	
	//Servo.Move(&Servo.rightSpeed, &Servo.leftSpeed, &Servo.MoveFlag
	wiringPiSetup();
	softServoSetup(LEFT, RIGHT, -1, -1, -1, -1, -1, -1);



	int speed = 750;
	while (speed >=-600)
	{
		cout << speed << endl;
		cout << "3" << endl;
		delay(1000);
		cout << "2" << endl;
		delay(1000);
		cout << "1" << endl;
		delay(1000);
		cout << "GO" << endl;
		UpdateSpeeds(750, speed);
		speed = speed + 50;
		delay(1000);
	}
	
	cout << "Successful exit..." << endl;
	UpdateSpeeds(0, 0);
	delay(1000);

	return 0;
}

void UpdateSpeeds(int left, int right)
{
	//Accepts -750 to 750: +ve go forward and -ve move back

	//Actual speed goes from -250 to 1250
	//Calculate the offset
	left = left + 500;
	right = right + 500;

	//Reverse left servo
	right = -right + 1000;

	for (int i = 0; i < 500; i++)
	{
		softServoWrite(RIGHT, right);
		softServoWrite(LEFT, left);
		delay(10); //10ms
	}
}
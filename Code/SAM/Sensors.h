#pragma once
#include <iostream>

using namespace std;
using namespace LibSerial;

//#define WHEEL_RADIUS 3.3
//#define BOT_RADIUS 5.8

class Sensors
{
private:
	int pingTop, pingBack, PhotoR, toggleRx, toggleTx;
	int EdgeDistance();
	double getDistance(int ping);
public:
	Sensors();
	~Sensors();

	int getToggle();
	int WaitForLight();
	int DetectEdge();
	int BackDistance();
}
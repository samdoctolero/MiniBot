#pragma once
#include <iostream>

using namespace std;
using namespace LibSerial;

//#define WHEEL_RADIUS 3.3
//#define BOT_RADIUS 5.8
#define PI 3.14159265358979323846

class Sensors
{
private:
	int pingTop, pingBack, PhotoR;
	int EdgeDistance();
	double getDistance(int ping);
public:
	Sensors();
	~Sensors();

	int WaitForLight();
	int DetectEdge();
	int BackDistance();
}
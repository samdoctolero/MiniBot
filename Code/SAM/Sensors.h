#pragma once
#include <iostream>

using namespace std;


//#define WHEEL_RADIUS 3.3
//#define BOT_RADIUS 5.8

class Sensors
{
private:
	int pingTop, pingBack, PhotoR, toggleRx, toggleTx;
	int EdgeDistance();
    double topDist;
    
	
public:
	Sensors();
	~Sensors();
    double getDistance(int ping);
	int getToggle();
	void WaitForLight();
	int DetectEdge(double dist);
	double BackDistance();
};
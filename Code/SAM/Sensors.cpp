#include "Sensors.h"
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <wiringPi.h>

Sensors::Sensors()
{
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup failed..." << endl;
		exit(1); //If setup fails then exit the main program
	}

	pingTop = 1;
	pingBack = 4;
	PhotoR = 6;
	toggleRx = 7;
	toggleTx = 0;
    
    topDist = getDistance(pingTop);
	pinMode(toggleRx, INPUT);
	pinMode(toggleTx, OUTPUT);
	digitalWrite(toggleTx, 1);
}

Sensors::~Sensors(){}

double Sensors::getDistance(int ping)
{
	pinMode(ping, OUTPUT);
	digitalWrite(ping, 0); //Reset to zero
	delay(2);
	//Start of transmission
	digitalWrite(ping, 1);
	delayMicroseconds(5);
	digitalWrite(ping, 0);
	//Activated PING to scan
	//Change pin mode to accept signals
	pinMode(ping, INPUT);
	//while (digitalRead(PING) == 0){ usleep(1); } //wait for the signal to turn high
	delayMicroseconds(750);
	//usleep = pulseIn(PING,1);
	//clock_t initTime = clock();
	//once the signal is high then measure how long it stays high;
	double utime = 0;
	while (digitalRead(ping) == 1)
	{
		delayMicroseconds(8);
		utime += 8;
	}
	//float timeDiff = (clock() - initTime) / (float)CLOCKS_PER_SEC; //seconds
	//double dist = (utime / 2000) * SOUND_SPEED; // (t/2)*(344m/s)*(100cm/1m)*(1s/1000us)
	return utime / 29 / 2;
}
void Sensors::WaitForLight()
{
	pinMode(PhotoR, INPUT);
	int read = 0;
	while (read == 0)
	{
		//if key pressed then exit
		read = digitalRead(PhotoR);
		//delay(1);
	}
}

double Sensors::BackDistance()
{
	return getDistance(pingBack);
}

int Sensors::getToggle()
{
	return toggleRx;
}

int Sensors::DetectEdge(double dist_base)
{

    if(getDistance(pingTop) <= dist_base)
    //if ((abs(getDistance(pingTop)) - dist_base)<2)
    { return 0;
    }
    else
	return 1;



}

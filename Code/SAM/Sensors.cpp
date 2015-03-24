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
	pingBack = 2;
	PhotoR = 22;
}

Sensors::~Sensors(){}

double getDistance(int ping)
{
	pinMode(ping, OUTPUT);
	digitalWrite(PING, 0); //Reset to zero
	delay(2);
	//Start of transmission
	digitalWrite(PING, 1);
	delayMicroseconds(5);
	digitalWrite(PING, 0);
	//Activated PING to scan
	//Change pin mode to accept signals
	pinMode(PING, INPUT);
	//while (digitalRead(PING) == 0){ usleep(1); } //wait for the signal to turn high
	delayMicroseconds(750);
	//usleep = pulseIn(PING,1);
	//clock_t initTime = clock();
	//once the signal is high then measure how long it stays high;
	double utime = 0;
	while (digitalRead(PING) == 1)
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
	pinMode(PHREST, INPUT);
	int read = 0;
	while (read == 0)
	{
		//if key pressed then exit
		read = digitalRead(PHREST);
		//delay(1);
	}
}

int Sensors::BackDistance()
{
	return getDistance(pingBack);
}

int Sensors::DetectEdge()
{
	double dist = getDistance(pingTop);
	//JENNY's CODE!!!!!!!!





}

#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <ctime>
#include <cmath>


using namespace std;
#define PING 1
#define SOUND_SPEED 344		//m/s
int main()
{
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup failed..." << endl;
		exit(1); //If setup fails then exit the main program
	}

	for (int i = 0; i <= 100;i++)
	{
		pinMode(PING, OUTPUT);
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
		double dist = utime/29/2;
		cout << "Duration(us): " << utime << endl;
		cout << "Distance(cm): " << dist << endl;
		delay(1000);
	}
	return 0;

}
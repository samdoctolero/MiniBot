/*
Start of the main program
*/

#include <iostream>
#include <wiringPi.h> //make sure to use -lwiringPi at the end of the compile command
#include <stdlib.h>

#define PHOTO_RES 6 //wiringPi pin 6 or GPIO 22 or 3rd pin from the bottom (close to audio jack) outside rung

using namespace std;

//Function prototypes
void WaitForLight(int pin);

int main()
{
	//wiringPi setup by Gordon. Maps and accesses gpios
	if (wiringPiSetup() == -1)
	{
		cout << "WiringPi setup faied..." << endl;
		exit(1); //If setup fails then exit the main program
	}

	WaitForLight(PHOTO_REST); //Stuck on this function until the Photoresistor senses a strong light




	return 0;
}


//Function definitions

/*
Loops continuously until the photoresistor senses enough light.
*/
void WaitForLight(int pin)
{
	pinMode(pin, INPUT);
	int read = 0;
	while (read == 0)
	{
		read = digitalRead(pin);
		delay(1); //rests for 1ms

		//This section is probably not needed
		//Included just in case the pin does not read a proper HIGH or LOW
		if (read != 0 or read != 1)
		{
			read = 0;
		}
	}
}
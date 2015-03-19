#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>
#include <ctime>
#include <cmath>


#define irLedPin 4          // IR Led on this pin
#define irSensorPin 5       // IR sensor on this pin

int irRead(int readPin, int triggerPin); //function prototype

void setup()
{
	pinMode(irSensorPin, INPUT);
	pinMode(irLedPin, OUTPUT);
	Serial.begin(9600); 
	// prints title with ending line break 
	Serial.println("Program Starting"); 
	// wait for the long string to be sent 
	delay(100); 
}

void loop()
{  
	Serial.println(irRead(irSensorPin, irLedPin)); //display the results
	delay(10); //wait for the string to be sent
}

/******************************************************************************
 * This function can be used with a panasonic pna4602m ir sensor
 * it returns a zero if something is detected by the sensor, and a 1 otherwise
 * The function bit bangs a 38.5khZ waveform to an IR led connected to the
 * triggerPin for 1 millisecond, and then reads the IR sensor pin to see if
 * the reflected IR has been detected
 ******************************************************************************/
int irRead(int readPin, int triggerPin)
{
	int halfPeriod = 13; //one period at 38.5khZ is aproximately 26 microseconds
	int cycles = 38; //26 microseconds * 38 is more or less 1 millisecond
	int i;
	for (i=0; i <=cycles; i++)
	{
		digitalWrite(triggerPin, HIGH); 
		delayMicroseconds(halfPeriod);
		digitalWrite(triggerPin, LOW); 
		delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
	}
	return digitalRead(readPin);
}
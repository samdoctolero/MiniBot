#pragma once

using namespace std;
class Bot
{

//Define pins
#define LEFT_SERVO 4				//Pin 4 controls left servo
#define RIGHT_SERVO 5				// Pin 5 controls right servo
#define PHOTO_RES 6					//wiringPi pin 6 or GPIO 22 or 3rd pin from the bottom (close to audio jack) outside rung
#define LEFT_IR_SENSOR 16			// Pin 15 & 16 to control left IR distance sensor & transmitter
#define LEFT_IR_TRANS 15
#define RIGHT_IR_SENSOR 11			// Pin 11 & 10 to control right IR distance sensor & transmitter
#define RIGHT_IR_TRANS 10
#define PING 1						//pin 1 to control ultrasonic sensor

//Robot specs
#define WHEEL_RADIUS 6.8			//cm


private:
	int LoopContinue;
	static const Dimension Arena = {100,100};	//cm
	static const Dimension Cube = {12.7,12.7};	//cm which is 5inches
	Dimension FrontCar;
	Dimension BackCar;
	Dimension Robot;



public:
	//structures
	struct Coordinate
	{
		double x; //cm
		double y; //cm
	};

	struct Coordinate
	{
		double length; //cm
		double width;  //cm
	};
	
	//variables
	Coordinate CurrPosition;				//Bot's current position
	Coordinate PrevPosition;				//Bot's previous position
	Coordinate CubePosition;				//Cube's position
	Coordinate CurrFrontPosition;			//Current Front Car's position
	Coordinate PrevFrontPosition;			//Previous Front Car's position
	Coordinate CurrBackPosition;			//Current Back Car's position
	Coordinate PrevbackPosition;			//Previous Back Car's posiion

	//constructor & destructor
	Bot();
	~Bot();

	//getters and setters
	int getLoopContinue();
	void setLoopContinue(int val);

	//methods
	void Begin();												//begins the main loop
	void MoveWheels(int LeftVal, int RightVal, int count);		//Rotate servos 
	void void WaitForLight();									//Pauses the bot until light is detected
	int BackLeftDistance();
	int BackRightDistance();
	int BackDistance();

};


#pragma once

using namespace std;
class Bot
{

#define PHOTO_RES 6					//wiringPi pin 6 or GPIO 22 or 3rd pin from the bottom (close to audio jack) outside rung


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

};


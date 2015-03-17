#pragma once
class Bot
{


#define LEFT_SERVO 4 //Pin 4 controls left servo
#define RIGHT_SERVO 1 // Pin 1 controls right servo
#define PHOTO_RES 6 //wiringPi pin 6 or GPIO 22 or 3rd pin from the bottom (close to audio jack) outside rung
#define LEFT_IR 2// Pin 0 to control left IR sensor
#define RIGHT_IR 3 //Pin 0 to control right IR sensor
#define PING 5 //pin 5 to control ultrasonic sensor



private:
	int LoopContinue;
	Dimension Arena;
	Dimension FrontCar;
	Dimension BackCar;
	Dimension Robot;
	Dimension Cube;



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
	Coordinate CurrPosition;
	Coordinate PrevPosition;
	Coordinate CurrCubePosition;

	//constructor & destructor
	Bot();
	~Bot();

	//getters and setters
	int getLoopContinue();
	void setLoopContinue(int val);

	//methods
	void Begin(); //begins the main loop
	void MoveWheels(int LeftVal, int RightVal, int count); //Rotate servos 
	void void WaitForLight(); //Pauses the bot until light is detected
	int BackLeftDistance();
	int BackRightDistance();
	int BackDistance();

};


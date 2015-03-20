#pragma once

using namespace std;


class Sensors
{
private:
	double PingDistance; //cm
	bool LeftObjectPresent; 
	bool RightObjectPresent;

public:
	enum SensorType
	{
		//numbers correspond to pins
		Ping = 1;
		LeftIRRx = 16;
		LeftIRTx = 15;
		RightIRRx = 11;
		RightRTx = 10 
	};

	Sensor(); //Constructor
	~Sensor();//Destructor

	double GetPingDistance();	//Grab the current distance from the class
	void PingScan();			//Tell the sensor to scan and change the PingDistance variable

	bool GetLeftObjectPresent();
	void LeftIRScan();

	bool GetRightObjectPresent();
	void RightIRScan();


};
#pragma once

class Servo
{
private:

	int Pin; //GPIO pin on the Raspi B+
	int Radius; //Wheel radius in cm

public:

	int GetPin(){ return Pin; }

	void SetPin(int PinNum);

	int GetRadius(){ return Radius; }

	void SetRadius(int RadNum);

	void Travel(int distance)
	{
		//Figure out distance and duration of loop relationship 

		int value;
		return softPwmWrite(this->Pin, value);
	}

	Servo();
	~Servo();

};


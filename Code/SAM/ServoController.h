#pragma once
#include <iostream>
#include <SerialStream.h>
#include <vector>

using namespace std;
using namespace LibSerial;

#define WHEEL_RADIUS 3.3
#define BOT_RADIUS 5.8
#define PI 3.14159265358979323846

class ServoController
{
public:
	struct wheel
	{
		float left;
		float right;
	};

	 enum Command
	{
		START = 0,
		FORWARD = 1,
		BACK = 2,
		STOP = 3,
	};

	 enum Cases
	 {
		 //Upper zone
		 BOTH_UPPER_MAX = 0,
		 LEFT_UPPER_MAX_RIGHT_UPPER_MIN = 2,
		 LEFT_UPPER_MIN_RIGHT_UPPER_MIN = 3,
		 LEFT_UPPER_MIN_RIGHT_UPPER_MAX = 4,

		 //lower zone
		 BOTH_LOWER_MAX = 5,
		 LEFT_LOWER_MAX_RIGHT_LOWER_MIN = 6,
		 LEFT_LOWER_MIN_RIGHT_LOWER_MIN = 7,
		 LEFT_LOWER_MIN_RIGHT_LOWER_MAX = 8
	 };

	ServoController();
	~ServoController();

	void reset();
	void flush();

	void BasicCMD(Command cmd);
	void AdjustHeading(double theta);

private:
	void requestSpeeds();
	void readSpeeds(wheel* p);
	void updateSpeeds(wheel p);
	bool echo();
	void rpm2time(wheel v, wheel* t);
	void time2rpm(wheel t, wheel* v);
	void rpm2angle(wheel rpm, wheel *theta);
	double angle2rpm(double theta);
	double deg2rad(double deg);
	double rad2deg(double rad);

	bool LeftInUpperZone(wheel cur, wheel uMax, wheel uMin);
	bool RightInUpperZone(wheel cur, wheel uMax, wheel uMin);

	Command state;
	string name;
	SerialStreamBuf::BaudRateEnum baudrate;
	SerialStreamBuf::CharSizeEnum charSize;
	SerialStreamBuf::ParityEnum parity;
	int stopBits;
	SerialStreamBuf::FlowControlEnum flowControl;
	SerialStream serialObj;
};
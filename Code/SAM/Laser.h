#pragma once
#include <iostream>
#include <SerialStream.h>
#include <vector>
#include "Point.h"
#include <algorithm>

#define _USE_MATH_DEFINES

using namespace std;
using namespace LibSerial;

class Laser
{
public:
	Laser();
	~Laser();
	void requestData();
	vector<vector<double> > getData(bool timeStamp, bool smooth);
	vector<Point> getDataCart(bool timeStamp, double maxDist, bool smooth);

	void flush();
	void reset();
private:
	string name;
	SerialStreamBuf::BaudRateEnum baudrate;
	SerialStreamBuf::CharSizeEnum charSize;
	SerialStreamBuf::ParityEnum parity;
	int stopBits;
	SerialStreamBuf::FlowControlEnum flowControl;

	int startStep;
	int endStep;
	int clusterCount;
	int scanInterval;
	int numScans;
	int expectedBytes;
	SerialStream serialObj;

	bool checkStatus();
	string extractDataSection(string reply, int numReads, int numValues);
	vector<double> decodeData(string data, int numValues);
	vector<vector<double> > calculateAngles(vector<double> distanceData);
};


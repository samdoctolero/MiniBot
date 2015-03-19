#pragma once
#include <iostream>
#include <SerialStream.h>
#include <vector>

using namespace std;
using namespace LibSerial;

class Laser
{
public:
	Laser();
	~Laser();
	void requestData();
	void getData(bool timeStamp);
	
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
	vector<float> decodeData(string data, int numValues);
	vector<vector<float> > calculateAngles(vector<float> distanceData);
};


#include "Laser.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <stdexcept>

Laser::Laser() : serialObj()
{
	name = "/dev/ttyACM0";

	serialObj.Open(name);

	baudrate = SerialStreamBuf::BAUD_19200;
	charSize = SerialStreamBuf::CHAR_SIZE_8;
	parity = SerialStreamBuf::PARITY_NONE;
	stopBits = 1;
	flowControl = SerialStreamBuf::FLOW_CONTROL_NONE;

	startStep = 44; //page 5
	endStep = 725; //page 5
	clusterCount = 2;
	scanInterval = 0;
	numScans = 1;
	expectedBytes = 1056;

	if (!serialObj.IsOpen())
	{
		cout << "throwing" << endl;
		throw runtime_error("Laser could not connect");
	}

	serialObj.SetBaudRate(baudrate);
	serialObj.SetCharSize(charSize);
	serialObj.SetNumOfStopBits(stopBits);
	serialObj.SetParity(parity);
	serialObj.SetFlowControl(flowControl);
}


Laser::~Laser()
{
	cout << "closing obj" << endl;
	serialObj.Close();
}



void Laser::reset()
{
	serialObj << "RS\n";
	checkStatus();
}

void Laser::flush()
{
	while (serialObj.rdbuf()->in_avail() > 0)
	{
		string trash;
		serialObj >> trash;
		cout << "flushing trash: " << trash << endl;
	}
	cout << "finished flushing data" << endl;
}

bool Laser::checkStatus()
{
	cout << "checking status" << endl;
	string echo;
	serialObj >> echo;
	string status;
	serialObj >> status;

	if ((status[0] == '0' && status[1] == '0') || (status[0] == '9' && status[1] == '9'))
		return true;
	cout << "Laser status not good! echo: " << echo << " status: " << status << endl;
	return false;
}

void Laser::requestData()
{
	stringstream ss;
	ss << "MD";
	ss << setw(4) << setfill('0') << startStep;
	ss << setw(4) << setfill('0') << endStep;
	ss << setw(2) << setfill('0') << clusterCount;
	ss << setw(1) << setfill('0') << scanInterval;
	ss << setw(2) << setfill('0') << numScans;
	string command = ss.str();

	cout << "command: " << ss.str() << endl;

	serialObj << ss.str() << "\n";

	checkStatus();
	checkStatus();
}

////////get data + helpers
void Laser::getData(bool timeStamp)
{
	if (timeStamp) //throw away the time stamp
	{
		string trash;
		serialObj >> trash;
		cout << "trash: " << trash << endl;
	}
	int numValues = ceil((double)(endStep - startStep + 1) / (double)clusterCount);
	int numReads = ceil(ceil(numValues*(195 / 64) / 65));

	char* buff = new char[expectedBytes];

	serialObj.read(buff, expectedBytes);
	
	string temp(buff);

	delete buff;
	
	for (int i = 0; i < temp.size(); i++)
	{
		if ((int)temp[i] == 10)
			cout << "NEW LINE(" << i << ")" << endl;
		else
			cout << (int)temp[i] << ",";
	}

	string dataSection = extractDataSection(temp, numReads, numValues);
	vector<float> distanceData = decodeData(dataSection, numValues);
	vector<vector<float> > data = calculateAngles(distanceData);

	cout << "data:" << endl << dataSection << endl;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << data[i][j] << " ";
		}
		if (i % 3 == 0)
			cout << endl;
		else
			cout << " : ";
	}
}

string Laser::extractDataSection(string reply, int numReads, int numValues)
{
	stringstream ss;

	for (int i = 0; i <= numReads; i++)
	{
		int dataStart = i*(64 + 2)+1; //64 chars + sum + new line
		int end;
		if (i == numReads) //if it is the last block of data it may not be a full 64 bytes
		{
			end = dataStart + (3 * numValues - 64 * i - 1); //calculate number of bytes left to read
			
		}
		else
			end = dataStart + 64; //read the whole 64 chars
		cout << "start: " << dataStart << "," << end << endl;
		for (int j = dataStart; j < end; j++)
		{
			ss << reply[j];
		}
	}
	return ss.str();
}

vector<float> Laser::decodeData(string data, int numValues)
{
	vector<int> dataInt;
	dataInt.reserve(data.length());

	for (int i = 0; i < data.length(); i++)
	{
		if (i == 0)
			cout << "first: " << (int)data[i] << endl;
		dataInt.push_back(((int)data[i]) - 48);
	}
	
	vector<float> dataMeters;
	dataMeters.reserve(numValues);
	for (int i = 0; i < dataInt.size() - 2; i+=3)
	{
		//pg 7
		int decoded = (dataInt[i] << 12) + (dataInt[i + 1] << 6) + (dataInt[i + 2]);
		dataMeters.push_back(decoded);
	}
	return dataMeters;
}

//[0] = distance, [1] = angle
vector<vector<float> > Laser::calculateAngles(vector<float> distanceData)
{
	float detectionRange = 239.77; //pg 5
	float angleStep = detectionRange*(float)clusterCount / (float)(endStep - startStep);
	
	float startAngle = 90 - (detectionRange / 2);

	vector<vector<float> > combined;
	combined.reserve(distanceData.size());
	for (int i = 0; i < distanceData.size(); i++)
	{
		float angle = startAngle + angleStep*i;
		if (distanceData[i] < 50.0)//assume distance is too far to measure
			distanceData[i] = 5000.0;
		if (distanceData[i] < 0.0)
		{
			cout << "neg" << endl;
			distanceData[i] = 0.0;
		}
		vector<float> temp;
		temp.push_back(distanceData[i]);
		temp.push_back(angle);
		combined.push_back(temp);
	}
	return combined;
}


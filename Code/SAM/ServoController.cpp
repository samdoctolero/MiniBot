#include "ServoController.h"
#include <iomanip>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <stdexcept>

ServoController::ServoController() : serialObj()
{
	name = "/dev/ttyACM0";

	serialObj.Open(name);

	baudrate = SerialStreamBuf::BAUD_9600;
	charSize = SerialStreamBuf::CHAR_SIZE_8;
	parity = SerialStreamBuf::PARITY_NONE;
	stopBits = 1;
	flowControl = SerialStreamBuf::FLOW_CONTROL_NONE;

	if (!serialObj.IsOpen())
	{
		cout << "throwing" << endl;
		throw runtime_error("Servo Controller could not connect");
	}

	serialObj.SetBaudRate(baudrate);
	serialObj.SetCharSize(charSize);
	serialObj.SetNumOfStopBits(stopBits);
	serialObj.SetParity(parity);
	serialObj.SetFlowControl(flowControl);

	state = STOP;

	serialObj << "+" << "\n";
}

ServoController::~ServoController()
{
	cout << "closing Servo Controller object" << endl;
	serialObj.Close();
}


void ServoController::flush()
{
	while (serialObj.rdbuf()->in_avail() > 0)
	{
		string trash;
		serialObj >> trash;
		cout << "flushing trash: " << trash << endl;
	}
	cout << "finished flushing data" << endl;
}

bool ServoController::echo()
{
	cout << "checking return value..." << endl;
	string echo;
	serialObj >> echo;
	
	if (echo == "+"){ return true; }
	return false;
}

void ServoController::requestSpeeds()
{
	serialObj << "?" << "\n";
}

void ServoController::readSpeeds(wheel* p)
{
	//cout << "Read speed function..." << endl;
	string read;
	serialObj >> read; //lefvalue,rightvalue
	//cout << "DB" << endl;
	stringstream split(read);
	string sleft,sright;
	getline(split, sleft, ',');
	getline(split, sright, ',');
	p->left = atof(sleft.c_str());//stod(sleft,sleft.length);
	p->right = atof(sright.c_str());//stod(sright, sright.length);
	//cout << "Read....Left: " << p->left << "\nRead...Right: " << p->right << endl;
	//flush();
}

void ServoController::updateSpeeds(wheel p)
{
		//cout << "Left: " << p.left << "\nRight: " << p.right << endl;
	//wheel check;
	//do{
		serialObj << "!" << p.left << "n" << p.right << "\n";
		//usleep(50);
		//requestSpeeds();
		//readSpeeds(&check);
		//cout << "Left: " << check.left << "\nRight: " << check.right << endl;
		//if (check.left != p.left)
		//{
		//	serialObj << "!" << p.left << "n" << p.right << "\n";
		//}
	//} while (check.left != p.left);
		
		//cout << "Angle return: " << rad2deg(angle.left - angle.right) << endl << endl;
		
}

void ServoController::rpm2time(wheel v, wheel* t)
{
	//convert left speed to time value
	float left_coeff[] = { 0.000079397867539, -0.000008387315216, -0.025517993613519, 0.017383531535494, 3.053430643307475, -1.428433472204044 };
	float right_coeff[] = { 0.000063662199825, -0.000044726129897, -0.022218488469861, 0.016615778380358, 2.651842625540850, -0.094073162720055 };

	int p = 5;
	t->left = 0;
	t->right = 0;
	
	//5th degree equation of the servos
	// t = a0*v^5 + a1*v^4 + a2*v^3 + a3*v^2 + a4*v + a5

	for (int i = 0; i <= 6; i++)
	{	
		t->left += left_coeff[i] * pow(v.left, p);
		t->right += right_coeff[i] * pow(v.right,p);
		p--;
	}
	//cout << "Inside rpm2time right: " << t->right << endl;
	//cout << "Inside rpm2time left: " << t->left << endl << endl;;

}

void ServoController::time2rpm(wheel t, wheel* v)
{
	//times 3 balances the conversion
	float left_coeff[] = { 0.000000000015917*3, 0.000000000175830*3, -0.000001743960122*3, -0.000012841081666*3, 0.073575313154103*3, 0.128618053017774*3 };
	float right_coeff[] = { 0.000000000015498*3, -0.000000000087903*3, -0.000001730469787*3, 0.000006846212420*3, 0.075616498674951*3, -0.111140054513122*3 };

	//left_coeff = left_coeff * 3;
	//right_coeff = right_coeff * 3;

	int p = 5;
	v->left = 0;
	v->right = 0;

	for (int i = 0; i <= 6; i++)
	{
		v->left += left_coeff[i] * pow(t.left, p);
		v->right += right_coeff[i] * pow(t.right, p);
		p--;
	}
	

}


void ServoController::BasicCMD(Command cmd)
{
	wheel update;
	switch (cmd)
	{
	case START:
		//send any random value to initiate the arduino
		update.left = 0.1;
		update.right = 0.1;
		state = START;
		updateSpeeds(update);
		break;
	case FORWARD:
		serialObj << "f" << "\n";
		state = FORWARD;
		break;
	case BACK:
		serialObj << "b" << "\n";
		state = BACK;
		break;
	case STOP:
		update.left = 0;
		update.right = 0;
		state = STOP;
		updateSpeeds(update);
		break;
	}
}
/*
void ServoController::AdjustHeading(double theta)
{
	double Half_rpm = angle2rpm(theta)/2;

	wheel curRPM;	//current speeds stored in the controller
	requestSpeeds();
	readSpeeds(&curRPM);
	
	wheel UmaxT = { 200, 200 }; //operational zones in time
	wheel UminT = {50,50};		//(-200,-50) && (50,200);
	wheel LminT= { -50, -50 };	//these values are different per wheel
	wheel LmaxT = {-200,-200};

	wheel UmaxRPM, UminRPM,LminRPM, LmaxRPM;
	time2rpm(UmaxT,&UmaxRPM);
	time2rpm(UminT, &UminRPM);
	time2rpm(LminT,&LminRPM);
	time2rpm(LmaxT,&LmaxRPM);

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
	//
	double rpmAvg = abs(curRPM.left + curRPM.right) / 2;
	wheel send;		//send values
	switch (state)
	{
	case FORWARD:
		if (Half_rpm > 0)
		{
			if ((LeftInUpperZone(curRPM, UmaxRPM, UminRPM)) && (RightInUpperZone(curRPM, UmaxRPM, UminRPM))
			{
				//decrease right
			}
		}
		else if (Half_rpm < 0)
		{

		}
	case BACK:
	
	}


	updateSpeeds();

}
*/

void ServoController::AdjustHeading(double theta)
{
	/*
	requestSpeeds();
	wheel curT;
	readSpeeds(&curT);
	//theta = deg2rad(theta);

	double rpm = theta * 15 / PI;

	double T = ((0.383*rpm + 0.2589)/2)*(0.0001); //increment/decrement variable
	cout << "Increment value: " << T << endl;

	if (theta > 0) //lean to the right
	{
		curT.right = curT.right - T;
		curT.left = curT.left + T;
	}
	else if (theta < 0)//lean to the left
	{
		curT.right = curT.right + T;
		curT.left = curT.left - T;
	}

	updateSpeeds(curT);
	*/
	serialObj << "t" << theta  << "\n";
	requestSpeeds();
	wheel read;
	readSpeeds(&read);
	//cout << "Read...Left: " << read.left << "|| right: " << read.right << endl;

}

double ServoController::deg2rad(double deg)
{
	return deg*PI / 180;
}
double ServoController::rad2deg(double rad)
{
	return rad * 180 / PI;
}
void ServoController::rpm2angle(wheel rpm, wheel* theta)
{
	theta->left = rpm.left *(WHEEL_RADIUS*PI) / (BOT_RADIUS * 30);
	theta->right = rpm.right*(WHEEL_RADIUS*PI) / (BOT_RADIUS * 30);
	
}
double ServoController::angle2rpm(double theta)
{
	return (theta * 30 * BOT_RADIUS) / (WHEEL_RADIUS*PI);
	/*
	rpm->left = theta.left * 30 * BOT_RADIUS / (WHEEL_RADIUS*PI);
	rpm->right = theta.right * 30 * BOT_RADIUS / (WHEEL_RADIUS*PI);
	*/
}

bool ServoController::LeftInUpperZone(wheel cur, wheel uMax, wheel uMin)
{
	if ((cur.left <= uMax.left) && (cur.left >= uMin.left))
	{
		return true;
	}
	return false;
}

bool ServoController::RightInUpperZone(wheel cur, wheel uMax, wheel uMin)
{
	if ((cur.right <= uMax.right) && (cur.right >= uMin.right))
	{
		return true;
	}
	return false;
}

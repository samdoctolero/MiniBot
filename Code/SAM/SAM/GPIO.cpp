#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "GPIO.h"
#include <chrono>
#include <thread>

using namespace std;

GPIO::GPIO()
{
	GPIO(23, true);
}

//function - true means write
GPIO::GPIO(int x, bool function)
{
	gpioNum = x;

	ostringstream convert;   // stream used for the conversion
	convert << gpioNum;
	strGpioNum = convert.str();

	string export_str = "/sys/class/gpio/export";
	ofstream of(export_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
	if (!of.is_open()){
		cout << " OPERATION FAILED: Unable to export GPIO" << strGpioNum << " ." << endl;
		return;
	}

	of << strGpioNum; //write GPIO number to export
	of.close(); //close export file
	
	//ifstream f;
	
	//do
	//{
	//	f.open("/sys/class/gpio/gpio" + strGpioNum + "/direction");
	//} while (!f.is_open());
	//cout << f.is_open() << f.good() << endl;
	//f.close();
	this_thread::sleep_for(chrono::seconds(2));
	this->setFunction(function);
}

GPIO::~GPIO()
{
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream of(unexport_str.c_str()); //Open unexport file
	if (!of.is_open()){
		cout << " OPERATION FAILED: Unable to unexport GPIO" << strGpioNum << " ." << endl;
		return;
	}

	of << strGpioNum; //write GPIO number to unexport
	of.close(); //close unexport file
}

void GPIO::setFunction(bool func)
{
	string dir = "in";
	if (func)
		dir = "out";

	string setdir_str = "/sys/class/gpio/gpio" + strGpioNum + "/direction";
	ofstream of(setdir_str.c_str()); // open direction file for gpio
	for (size_t i = 0; i < 10000; i++);
	if (!of.is_open()){
		cout << " OPERATION FAILED: Unable to set function of GPIO" << strGpioNum << " ." << endl;
		cout << of.is_open() << " " << of.good() << endl;
		return;
	}

	of << dir; //write direction to direction file
	of.close(); // close direction file
}

void GPIO::setValue(bool val)
{
	string setval_str = "/sys/class/gpio/gpio" + strGpioNum + "/value";
	ofstream of(setval_str.c_str()); // open value file for gpio
	if (!of.is_open()){
		cout << " OPERATION FAILED: Unable to set the value of GPIO" << strGpioNum << " ." << endl;
		return;
	}

	string outVal = "0";
	if (value)
		outVal = "1";

	of << outVal;//write value to value file
	of.close();// close value file 
	value = val;
}

bool GPIO::getValue()
{
	return value;
}

int GPIO::getGpioNum()
{
	return gpioNum;
}

/*GPIO::GPIO()
{
	this->gpionum = "4"; //GPIO4 is default
}

GPIO::GPIO(string gnum)
{
	this->gpionum = gnum;  //Instatiate GPIO object for GPIO pin number "gnum"
}

int GPIO::export_gpio()
{
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
	if (exportgpio < 0){
		cout << " OPERATION FAILED: Unable to export GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	exportgpio << this->gpionum; //write GPIO number to export
	exportgpio.close(); //close export file
	return 0;
}

int GPIO::unexport_gpio()
{
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str()); //Open unexport file
	if (unexportgpio < 0){
		cout << " OPERATION FAILED: Unable to unexport GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	unexportgpio << this->gpionum; //write GPIO number to unexport
	unexportgpio.close(); //close unexport file
	return 0;
}

int GPIO::setdir_gpio(string dir)
{

	string setdir_str = "/sys/class/gpio/gpio" + this->gpionum + "/direction";
	ofstream setdirgpio(setdir_str.c_str()); // open direction file for gpio
	if (setdirgpio < 0){
		cout << " OPERATION FAILED: Unable to set direction of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	setdirgpio << dir; //write direction to direction file
	setdirgpio.close(); // close direction file
	return 0;
}

int GPIO::setval_gpio(string val)
{

	string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
	if (setvalgpio < 0){
		cout << " OPERATION FAILED: Unable to set the value of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	setvalgpio << val;//write value to value file
	setvalgpio.close();// close value file 
	return 0;
}

int GPIO::getval_gpio(string& val){

	string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ifstream getvalgpio(getval_str.c_str());// open value file for gpio
	if (getvalgpio < 0){
		cout << " OPERATION FAILED: Unable to get value of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	getvalgpio >> val;  //read gpio value

	if (val != "0")
		val = "1";
	else
		val = "0";

	getvalgpio.close(); //close the value file
	return 0;
}

string GPIO::get_gpionum(){

	return this->gpionum;

}*/
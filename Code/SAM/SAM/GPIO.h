#pragma once

#include <string>
using namespace std;
/* GPIO Class
* Purpose: Each object instantiated from this class will control a GPIO pin
* The GPIO pin number must be passed to the overloaded class constructor
*/
class GPIO
{
public:
	GPIO();  // create a GPIO object that controls GPIO4 (default
	GPIO(int x, bool function); // create a GPIO object that controls GPIOx, where x is passed to this constructor
	~GPIO();
	void setFunction(bool func); // Set GPIO Direction
	void setValue(bool val); // Set GPIO Value (output pins)
	bool getValue(); // Get GPIO Value (input/ output pins)
	int getGpioNum(); // return the GPIO number associated with the instance of an object
private:
	int gpioNum; // GPIO number associated with the instance of an object
	string strGpioNum;
	bool value;
};
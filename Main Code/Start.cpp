/*
Start of the main program
*/

#include <iostream>
#include <stdlib.h>
#include "Bot.h"

using namespace std;


int main()
{

	//Initialize Robot before photoresistor so the bot is ready to go on signal
	Bot MiniBot();

	MiniBot.WaitForLight(); //Stuck on this function until the Photoresistor senses a strong light

	//Main Loop start
	MiniBot.Begin();



	return 0;
}


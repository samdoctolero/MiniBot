#include "rpiPWM1.h"

#define LEFT 0x200000
#define RIGHT 0x000000

int main (void){
        
    rpiPWM1 LeftServo(500.0, 256, 80.0, rpiPWM1::MSMODE);
	//rpiPWM1 RightServo(500.0, 256, 80.0, rpiPWM1::MSMODE, RIGHT)
    // initialize PWM1 output to 1KHz 8-bit resolution 80% Duty Cycle & PWM mode is MSMODE
    //unsigned int dcyccount = 0; // reset Duty Cycle to Zero
	//dcyccount != 256
    while(true){
        LeftServo.setDutyCycleCount(0); // increase Duty Cycle by 16 counts every two seconds
		//RightServo.setDutyCycleCount(0);
        //dcyccount += 16;// until we hit 256 counts or 100% duty cycle
       // printf("Duty Cycle is %3.2lf \n",pwm.getDutyCycle());
        //printf("Divisor is %d\n", pwm.getDivisor());
        usleep(2000000);
    }
    return 0;
}

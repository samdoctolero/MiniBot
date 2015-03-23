#include <Servo.h>
#include <math.h>

//#include <string>

#define R_WHEEL 3.3    //cm
#define R_VEHICLE 5.8  //cm
#define REQ_V "?"
#define CH_V "!"
#define ECHO "+\n"
#define COMMA ","

void rpm2time(float left, float right, float* Tleft, float* Tright);

void time2rpm(float Tleft, float Tright, float* left, float* right);

Servo left, right;
float in_left = 1530;
float in_right = 1470;
const float pi = 3.14159265359;

float vleft = 30; //range -200 to 200
float vright = 30; //range -200 to 200
void setup() {
  // put your setup code here, to run once:
  
  //left.attach(6);
  //right.attach(5);
  Serial.begin(9600);
  Serial.print(ECHO);
  //left.writeMicroseconds(1500);
  //right.writeMicroseconds(1500);
  while(!(Serial.available()))
  {}
  //left.writeMicroseconds(in_left);
  //right.writeMicroseconds(in_right);
  Serial.flush();
  Serial.print(ECHO);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
      
       char str = Serial.read();
       //Serial.print(str);
         if (str == '!')
         {
           float rpmLeft = Serial.parseFloat();
           float rpmRight = Serial.parseFloat();
           rpm2time(rpmLeft,rpmRight,&vleft,&vright);
           Serial.flush();
           Serial.print(ECHO);
           
           
           //update the servo pwm as well
         }
         else if(str == '?')
         {
           float rpmLeft, rpmRight;
           time2rpm(vleft,vright, &rpmLeft, &rpmRight);
           String ret;
           ret.concat(rpmLeft);
           ret.concat(",");
           ret.concat(rpmRight);
           ret.concat("\n");
           Serial.print(ret);
           Serial.flush();
         }
        else{}
       Serial.flush();
        
        //Serial.print("vleft: ");Serial.print(vleft);Serial.print("\n");
        //Serial.print("vright: ");Serial.print(vright);Serial.print("\n"); 
  }
}

void rpm2time(float left, float right, float* Tleft, float* Tright)
{
  	float left_coeff[] = { 0.000079397867539, -0.000008387315216, -0.025517993613519, 0.017383531535494, 3.053430643307475, -1.428433472204044 };
	float right_coeff[] = { 0.000063662199825, -0.000044726129897, -0.022218488469861, 0.016615778380358, 2.651842625540850, -0.094073162720055 };

	int p = 5;
	*Tleft = 0;
	*Tright = 0;
	
	//5th degree equation of the servos
	// t = a0*v^5 + a1*v^4 + a2*v^3 + a3*v^2 + a4*v + a5

	for (int i = 0; i < 6; i++)
	{	
		*Tleft += left_coeff[i] * pow(left, p);
		*Tright += right_coeff[i] * pow(right,p);
		p--;
	}
}
void time2rpm(float Tleft, float Tright, float* left, float* right)
{
      	float left_coeff[] = { 0.000000000015917, 0.000000000175830, -0.000001743960122, -0.000012841081666, 0.073575313154103, 0.128618053017774 };
	float right_coeff[] = { 0.000000000015498, -0.000000000087903, -0.000001730469787, 0.000006846212420, 0.075616498674951, -0.111140054513122 };

	int p = 5;
	*left = 0;
	*right = 0;

	for (int i = 0; i < 6; i++)
	{
		*left += left_coeff[i] * pow(Tleft, p);
		*right += right_coeff[i] * pow(Tright, p);
		p--;
	}
}

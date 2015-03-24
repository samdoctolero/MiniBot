
/*
Commands:
!<left_val>n<right_val> = change speeds 
? = get speeds in rpm
d = get distance
a = get angle
r = reset (put all to zero);
t = given angular rate
f = move forward
b = move back;


*/
#include <Servo.h>
#define ECHO "+\n"
#define R_WHEEL 3.3    //cm
#define R_VEHICLE 5.8  //cm
#define DELAY 0.1 //ms
float PleftT = 0;
float PrightT = 0;

float leftT = 1500;
float rightT = 1500;

Servo left, right;

void GivenHeading(float theta);
void UpdateParams(float l,float r);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.print(ECHO);
  left.attach(5);
  right.attach(6);
  left.writeMicroseconds(leftT);
  right.writeMicroseconds(rightT);
  //Serial.print(ECHO);
  while(!(Serial.available())){}
  //Serial.print(ECHO);
 Serial.flush();
 //Serial.print(ECHO);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(Serial.available())
  {
    char str = Serial.read();
    if(str == '!')
    {
     // Serial.print(ECHO);
      PleftT = Serial.parseFloat(); //these are in rpm
      PrightT = Serial.parseFloat(); 
      
       //Serial.flush();
        
      //cap it at between -200 and 200;
      UpdateParams(PleftT,PrightT);
      //Serial.print(ECHO);
        
    }
    else if(str == '?')
    {
     //Serial.flush();
      //Serial.print(ECHO);
      String ret;
      ret.concat(PleftT);
      ret.concat(',');
      ret.concat(PrightT);
      ret.concat("\n");
      Serial.print(ret);
      //Serial.flush();
     // Serial.print(ECHO);
    }
    else if(str == 't')
    {
      //Serial.print(ECHO);
      float theta = Serial.parseFloat();
      GivenHeading(theta);
      //Serial.print(ECHO);
    }
    /*
    else if(str == 'd')
    {
      Serial.print(distance);
      Serial.print("\n");
      Serial.print((rpm_left + rpm_right)/2);
      distance = 0; //reset distance count;
      Serial.flush();
    }
    else if(str == 'a')
    {
      Serial.print(angle);
      Serial.print("\n");
      angle = 0;
      Serial.flush();
    }*/
    else if(str == 'r')
    {
      left.writeMicroseconds(1500);
      right.writeMicroseconds(1500);
      
      PrightT = 0;
      PleftT = 0;
      
      //Serial.print(ECHO);
    }
    else if(str == 'f')
    {
      UpdateParams(70,70);
      //Serial.print(ECHO);
    }
    else if(str == 'b')
    {
      UpdateParams(-40,-40);
      //Serial.print(ECHO);
    }
    else
    {
      //Serial.print("-\n");
      Serial.flush();
    }
  }
   delay(DELAY); //0.1ms delay

}

void GivenHeading(float theta)
{
  double a = 1000;
  float rpm = theta*15/PI;
  float T = a*((0.383*rpm+0.2589)/2)*0.0001;
  
  if(theta > 0)
  {
    PleftT = PleftT + T;
    PrightT = PrightT - T;
    UpdateParams(PleftT,PrightT);
    
  }
  if (theta < 0)
  {
    PleftT = PleftT - T;
    PrightT = PrightT + T;
    UpdateParams(PleftT,PrightT);
  }
}

void UpdateParams(float l, float r)
{
  PleftT = l;
  PrightT = r;
  
  if(PleftT > 110){PleftT = 110;}
      else if(PleftT <-110){PleftT = -110;}
      
       if(PrightT > 110){PrightT = 110;}
      else if(PrightT <-110){PrightT = -110;}
      
      if(PleftT < 5 && PleftT > -5){PleftT = 0;}
      if(PrightT < 5 && PrightT > -5){PrightT = 0;}
      
      
        leftT = -PleftT + 1500;
        rightT = PrightT + 1500;
        left.writeMicroseconds(leftT);
        right.writeMicroseconds(rightT);
  
}

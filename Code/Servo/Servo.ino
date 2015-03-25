
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
double PleftT = 0;
double PrightT = 0;

double leftT = 1500;
double rightT = 1500;

Servo left, right;

void GivenHeading(double theta);
void UpdateParams(double l,double r);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.print(ECHO);
  left.attach(6);
  right.attach(5);
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
      double theta = Serial.parseFloat();
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
      UpdateParams(30,30);
      //Serial.print(ECHO);
    }
    else if(str == 'b')
    {
      UpdateParams(-25,-25);
      //Serial.print(ECHO);
    }
    else
    {
      //Serial.print("-\n");
      Serial.flush();
    }
  }
  Serial.flush();
   delay(DELAY); //0.1ms delay

}

void GivenHeading(double theta)
{
  double a = 1;
  double l = 1;
  double r = 1;
  double rpm = abs(theta*15/PI);
  double T = a*((1.5943*rpm-0.0638))*DELAY;
  double TL = l*T;
  double TR = r*T;
  
  if(theta > 0)
  {
    PleftT = PleftT + TL;
    PrightT = PrightT - TR;
    UpdateParams(PleftT,PrightT);
    
  }
  if (theta < 0)
  {
    PleftT = PleftT - TL;
    PrightT = PrightT + TR;
    UpdateParams(PleftT,PrightT);
  }
}

void UpdateParams(double l, double r)
{
  PleftT = l;
  PrightT = r;
  
  if(PleftT > 110){PleftT = 110;}
      else if(PleftT <-110){PleftT = -110;}
      
       if(PrightT > 110){PrightT = 110;}
      else if(PrightT <-110){PrightT = -110;}
      
      if(PleftT < 5 && PleftT > -5){PleftT = 0;}
      if(PrightT < 5 && PrightT > -5){PrightT = 0;}
      
      
        leftT =  (PleftT + 1500);
        rightT =  (-PrightT + 1500);
        left.writeMicroseconds(leftT);
        right.writeMicroseconds(rightT);
  
}

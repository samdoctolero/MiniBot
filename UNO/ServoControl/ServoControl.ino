/*
Commands:
!<left_val>n<right_val> = change speeds 
? = get speeds in rpm
d = get distance
a = get angle
r = reset (put all to zero);


*/
#include <Servo.h>
#define ECHO '+'
#define R_WHEEL 3.3    //cm
#define R_VEHICLE 5.8  //cm
//#define PI 3.14159265359

//function prototypes:
float rpm2angle(float rpm);
float Lrpm2time(float rpm);
float Rrpm2time(float rpm);
float Rtime2rpm(float time);
float Ltime2rpm(float time);


Servo left, right;//servos

//globall variables
float act_left = 1500;//actual values used for 
float act_right = 1500;//the Microseconds function

float pseudo_left = 0; //range -200 to 200
float pseudo_right = 0; //range -200 to 200

float rpm_left = 0;
float rpm_right = 0;
//distance and angle:
float distance = 0;    //cm
float angle = 0;  //radians

void setup() {
  // put your setup code here, to run once:
  
  left.attach(6); //left wheel
  right.attach(5); //right wheel
  Serial.begin(9600);
  
  //initially stop the servos
  left.writeMicroseconds(1500);
  right.writeMicroseconds(1500);
  Serial.print(ECHO);
  while(!(Serial.available()))
  {}
  //once a signal is sent then move forward
  left.writeMicroseconds(act_left);
  right.writeMicroseconds(act_right);
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available())
  {
    char str = Serial.read();
    if(str == '!')
    {
      rpm_left = Serial.parseFloat(); //these are in rpm
      rpm_right = Serial.parseFloat(); 
      
      //convert to pseudo left /right
      if (rpm_left == 0){pseudo_left = 0;}
      else{pseudo_left = Lrpm2time(rpm_left);} 
      if(rpm_right == 0){pseudo_right = 0;}
      else{pseudo_right = Rrpm2time(rpm_right);}
      
        Serial.flush();
        Serial.print(ECHO);
        
      //cap it at between -200 and 200;
      if(pseudo_left > 200){pseudo_left = 200;}
      else if(pseudo_left <-200){pseudo_left = -200;}
      
       if(pseudo_right > 200){pseudo_right = 200;}
      else if(pseudo_right <-200){pseudo_right = -200;}
      
        act_left = -pseudo_left + 1500;
        act_right = pseudo_right + 1500;
        left.writeMicroseconds(act_left);
        right.writeMicroseconds(act_right);
        
    }
    else if(str == '?')
    {
      String ret;
      ret.concat(pseudo_left);
      ret.concat(',');
      ret.concat(pseudo_right);
      ret.concat("\n");
      Serial.print(ret);
      Serial.flush();
    }
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
    }
    else if(str == 'r')
    {
      left.writeMicroseconds(0);
      right.writeMicroseconds(0);
      
      rpm_left = 0;
      rpm_right = 0;
      
      pseudo_left = 0;
      pseudo_right = 0;
      
      Serial.print(ECHO);
    }
    else{}
    Serial.flush();
  }
  
  delay(5);
  float rpmAvg = (rpm_left + rpm_right)/2;
  distance = distance + (6/10)*PI*R_WHEEL*rpmAvg;
  //Serial.print(rpmAvg);
  //Serial.print(distance);
  angle = angle + rpm2angle(rpm_left - rpm_right)*5/60000;
}

//function definitions:
float rpm2angle(float rpm)
{
  return rpm*R_WHEEL*PI/(R_VEHICLE*30);
}
float Lrpm2time(float rpm)
{
  float a[] = {-1.48341798734790*pow(10,-15),6.26353501441764*pow(10,-13),1.52937036226030*pow(10,-11),-3.63663750581681*pow(10,-9),-5.20479128471109*pow(10,-8),7.03334211796386*pow(10,-6),7.25603033376723*pow(10,-5),-0.00498823236846572,-0.0358356299618135,2.48125826897494,0.667217361684585};
  float time = 0;
  int p = 10;
  for(int i = 0;i<=10;i++)
  {
    time = time + a[i]*pow(rpm,p);
    p--;
  }
  return time;
}
float Rrpm2time(float rpm)
{
  float a[] = {5.18782017571504*pow(10,-10),-2.92705379673237*pow(10,-8),-2.44762588447632*pow(10,-6),5.90339849337241*pow(10,-5),0.00313583474371239,-0.0307746635068073,0.651451633130987,3.88004083839639};
  int p = 8;
  float time = 0;
  for(int i = 0;i<=8;i++)
  {
    time = time + a[i]*pow(rpm,p);
    p--;
  }
  return time;
}
float Rtime2rpm(float time)
{
   float a[] = {-3.64324487530392*pow(10,-22),-9.10162496406684*pow(10,-20),4.90813445517008*pow(10,-17),8.28125753436474*pow(10,-15),-2.24778552602702*pow(10,-12),-1.87309930528302*pow(10,-11),3.94108639195889*pow(10,-8),-1.70613092235068*pow(10,-5),-0.000166560929855704,0.707859649041834,-0.874106164348319};
  float rpm = 0;
  int p = 10;
  for(int i = 0;i<=10;i++)
  {
    rpm = rpm + a[i]*pow(time,p);
    p--;
  }
  return rpm;
}
float Ltime2rpm(float time)
{
  float a[] = {-2.61982935679808*pow(10,-22),-1.00929628050659*pow(10,-19),4.15379343562855*pow(10,-17),9.10086593983839*pow(10,-15),-2.42732434791387*pow(10,-12),-2.85645232493729*pow(10,-11),6.36974909735346*pow(10,-8),-1.71907717874871*pow(10,-5),-0.000714074780309386,0.686973048567207,2.01892842572820};
  float rpm = 0;
  int p = 10;
  for(int i = 0;i<=10;i++)
  {
    rpm = rpm + a[i]*pow(time,p);
    p--;
  }
  return rpm;
}

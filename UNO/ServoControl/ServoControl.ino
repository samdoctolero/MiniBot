#include <Servo.h>

#define ECHO '+'
//#define R_WHEEL 3.3    //cm
//#define R_VEHICLE 5.8  //cm
Servo left, right;
float act_left = 1500;//actual values used for 
float act_right = 1500;//the Microseconds function

float pseudo_left = 0; //range -200 to 200
float pseudo_right = 0; //range -200 to 200


void setup() {
  // put your setup code here, to run once:
  
  left.attach(6); //left wheel
  right.attach(5); //right wheel
  Serial.begin(9600);
  
  //initially stop the servos
  left.writeMicroseconds(1500);
  right.writeMicroseconds(1500);
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
      pseudo_left = Serial.parseFloat();
      pseudo_right = Serial.parseFloat();
      
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
    else{}
    Serial.flush();
  }
}

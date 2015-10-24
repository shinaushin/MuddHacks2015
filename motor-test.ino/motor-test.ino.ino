#include <Servo.h>

Servo motor;
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("HELLO");
  motor.attach(11);
} 
 double pos;
 
void loop() 
{ 
  Serial.println("HI");
  pos = 0;
  motor.write(pos);
  pos += 10;
  delay(1000);
}

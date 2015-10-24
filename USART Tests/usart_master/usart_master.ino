#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13);

int incomingByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  while(!Serial);
  while(!mySerial);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() > 0) {
    char buff[1];
    mySerial.readBytes(buff, 1);
    if (buff[0] == 'H') {
      Serial.println("HELLO");
    }
    if (buff[0] == 'L') {
      Serial.println("HI");
    }
  }
}

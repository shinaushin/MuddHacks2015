#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13);

void setup() {
  mySerial.begin(9600);
  while(!mySerial);
}

void loop() {
  mySerial.print('H');
  delay(1000);
  mySerial.print('L');
  delay(1000);
}



#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
#include<SoftwareSerial.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

SoftwareSerial mySerial(12,13);

int maxP = 32;
int maxV = 64;

// Update the matrix given the position and velocity of the stylus
void color(RGBmatrixPanel mat, int x, int y, float xVel, float yVel)
{
  long hue = sqrt(pow(xVel,2) + pow(yVel,2));
  uint8_t saturation = xVel * 255 / maxV;
  uint8_t value = yVel*255 / maxV;

  if (saturation > 255) saturation = 255;
  if (value > 255) value = 255;

  mat.drawPixel(x, y, mat.ColorHSV(hue, saturation, value, true));
}

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  mySerial.begin(9600);
  while(!mySerial);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    int x = mySerial.parseInt();
    int y = mySerial.parseInt();
    float xVel = mySerial.parseFloat();
    float yVel = mySerial.parseFloat();
    color(matrix, x, y, xVel, yVel);
  }
}


#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int maxP = 32;
int maxV = 64;

// Update the matrix given the position and velocity of the stylus
void color(RGBmatrixPanel matrix, double x, double y, double xVel, double yVel)
{
  long hue = sqrt(pow(xVel,2) + pow(yVel,2));
  uint8_t saturation = xVel * 255 / maxV;
  uint8_t value = yVel*255 / maxV;

  if (saturation > 255) saturation = 255;
  if (value > 255) value = 255;

  matrix.drawPixel((int)x, (int)y, matrix.ColorHSV(hue, saturation, value, true));
}

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
}



void loop() {
  // put your main code here, to run repeatedly:
  
}

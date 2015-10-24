
#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
#include <FFT.h>

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
// If your matrix has the DOUBLE HEADER input, use:
/*#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT 9
#define OE  10
#define A   A3
#define B   A2
#define C   A1
#define D   A0*/
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void setup() {
  // put your setup code here, to run once:
  matrix.begin();

  // (0, 0) is red
  matrix.drawPixel(0, 0, matrix.Color333(1, 0, 0));

  // (31, 31) is green
  matrix.drawPixel(31, 31, matrix.Color333(0, 1, 0));
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

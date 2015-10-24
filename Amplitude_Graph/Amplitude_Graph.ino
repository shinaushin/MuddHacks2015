#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
int mic = A0;
int radius = 0;
// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 8  
#define OE  9
#define LAT 10
#define A   A4
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
int y;

void setup() {
  pinMode(mic, INPUT);
  matrix.begin();
  Serial.begin(9600);
  y = 0;
}

void loop() {
  
  double threshhold = 0.5;
  double amp = amplitude();
  
  //map the x-coordinate proportionally to amplitude
  int x = 31 * (amp / threshhold);
  if (x > 31) x = 31;
  
  if (x > radius) {
   paint(radius, x);
   radius = x; 
  }
  else {
   int temp = pow(2, -radius);
   
   for (int i = temp; i <= radius; i++) {
    matrix.drawCircle(15,15,i,matrix.Color333(0,0,0)); 
   }
   
   radius = temp;
  }
  
  
}

double amplitude() {
   int sample = analogRead(mic);
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < 50)
   {
      sample = analogRead(mic);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts 
   return volts;
}

void paint(int rad1, int rad2) {
 //paint a red line from (0, y) up to (x,y) such that (x,y) corresponds to (intensity, time);
  for (int i = rad1; i <= rad2; i++) {
    double r = 0;
    double g = 0;
    double b = 0;
    
    double k = 15*i/32.0;
    int j = (int) k;  
    if (j < 5) {
      r = 7*(10-j)/10.0;
      g = 7*j/8.0;
      b = 0;
      matrix.drawCircle(15, 15, j, matrix.Color333(r,g,b));
    } else if (j < 8) {
      r = 7*(10-j)/10.0;
      g = 7*j/8.0;
      b = 7*(j-5)/10;
      matrix.drawCircle(15, 15, j, matrix.Color333(r,g,b));
    } else if (j < 10) {
      r = 7*(10-j)/10.0;
      g = 7*(15-j)/8.0;
      b = 7*(j-5)/10; 
      matrix.drawCircle(15, 15, j, matrix.Color333(r,g,b));
    } else {
      r = 0;
      g = 7*(15-j)/8.0;
      b = 7*(j-5)/10;
      matrix.drawCircle(15, 15, j, matrix.Color333(r,g,b));
    }
    
  }
}

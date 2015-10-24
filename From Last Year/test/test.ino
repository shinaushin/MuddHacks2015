#include <ffft.h>
#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

void setup() {
  pinMode(outPin, OUTPUT);
  pinMode(mic, INPUT);
  Serial.begin(9600);
}

void loop() {
  double threshhold = 0.5;
  double amp = amplitude();
  Serial.println(amp);
  analogWrite(outPin, 255.0 * (amp / threshhold));
  delay(10);
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
      sample = analogRead(0);
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

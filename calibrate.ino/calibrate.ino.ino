#include <StandardCplusplus.h>
#include <vector>

using namespace std;

int sensorPin = A0;

double minPoint = 0.2;
double maxPoint = 0.5;
double meas = 0.2;
int numPoints = 5;

void setup() 
{ 
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.print("Hold sensor at ");
  Serial.print(meas);
  Serial.println(" m, then type 1 and enter");
} 

vector<vector <double> > points;
double sum = 0.0;
bool printed = false;
void loop() 
{ 
  if (meas >= maxPoint && !printed) {
    for (int i = 0; i < numPoints; ++i) {
      Serial.print(points[i][0]);
      Serial.print(": ");
      Serial.println(points[i][1]);
      printed = true;
    }
  }
  else if (Serial.available())
  {
    Serial.parseInt();
    for (int i = 0; i < 300; ++i) {
      sum += analogRead(sensorPin);
      delay(10);
    }
    vector<double> point;
    point.push_back(meas);
    point.push_back(sum / 300);
    sum = 0;
    points.push_back(point);
    meas += (maxPoint - minPoint)/numPoints;

    Serial.print("Hold sensor at ");
    Serial.print(meas);
    Serial.println(" m, then type 1 and enter");
  }
} 

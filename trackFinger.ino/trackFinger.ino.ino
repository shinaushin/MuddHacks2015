#include<Servo.h>
#include<StandardCplusplus.h>
#include<list>
#include<SoftwareSerial.h>

using namespace std;

SoftwareSerial mySerial(12,13);

const double pi = 3.14159;

int sensorA = A0;
int sensorB = A1;
int sensorC = A2;
int motorPinA = A3;
int motorPinB = A4;
int motorPinC = A5;

Servo motorA;
Servo motorB;
Servo motorC;

// The number of samples to remember in determining velocity
const int numSamps = 10;

// The most recent samples, used to determine velocity
list<double> sampsX;
list<double> sampsY;

double thetaA = 0;
double thetaB = 0;
double thetaC = 0;

double L = .19;

double fs = 1;  // sampling frequency, Hz

// Update the average velocity without recomputing
// Given a list of prior samples and a new sample,
// modify the list by removing the oldest sample and adding the new
// Remove the first velocity from the average and add the new velocity
// Theta(1)
double updateVAve(double oldV, list<double>& oldSamples, double newSample)
{
  
  // Find the earliest v and remove it from the average
  double first = *(oldSamples.erase(oldSamples.begin()));
  double second = *(oldSamples.begin());
  double vFirst = (numSamps - first) / fs;
  oldV -= (vFirst / numSamps);

  // Compute the new v and add it to the average
  double last = *(--oldSamples.end());
  double newV = (newSample - last) / fs;
  oldV += (newV / numSamps);

  // Add the new sample
  oldSamples.push_back(newSample);

  return oldV;
}

// Compute the average velocity over the last numSamps samples
// Theta(n)
double computeVAve(list<double> samples)
{
  double sum = 0;
  
  list<double>::iterator first = samples.begin();
  list<double>::iterator second = ++samples.begin();
  while (first != samples.end() && second != samples.end()) {
    sum += (*second - *first)/fs;
    ++first;
    ++second;
  }
  return sum / samples.size();
}

// Convert an analog voltage read from a distance sensor to a distance
double linearize(double sample)
{
  
  double k0 = 1.2637;
  double k1 = -0.005126;
  double k2 = 9.5074 * pow(10.0,-6.0);
  double k3 = -7.0759 * pow(10.0, -9.0);
  return k0 + k1*sample + k2*pow(sample, 2) + k3*pow(sample,3);
  
  //return 27.0 / sample;
}

// Calculate the position in cartesian coordinates and store it in x and y
void findPos(double a, double b, double c, double& x, double& y)
{
  x = b*cos(thetaB) - .2;
  y = L - (a*cos(thetaA) - .2);
}

void setup() 
{
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(sensorC, INPUT);
  motorA.attach(motorPinA);
  motorB.attach(motorPinB);
  motorC.attach(motorPinC);

  mySerial.begin(9600);
  Serial.begin(9600);
  while(!mySerial);
}

double vAveX = 0;
double vAveY = 0;
void loop() 
{
  
  // Read from sensors
  double sampA = linearize(analogRead(sensorA));
  double sampB = linearize(analogRead(sensorB));
  double sampC = linearize(analogRead(sensorC));

  // Remember samples
  double x,y;
  findPos(sampA, sampB, sampC, x, y);

  if (sampsX.size() > numSamps) {
    // If we've already filled the list of past samples, just update vAve
    vAveX = updateVAve(vAveX, sampsX, x);
    vAveY = updateVAve(vAveY, sampsY, y);
  }
  else {
    // The list isn't full yet, add a new sample and compute vAve
    sampsX.push_back(x);
    sampsY.push_back(y);
    vAveX = computeVAve(sampsX);
    vAveY = computeVAve(sampsY);
  }

  // Adjust thetaA
  double gammaA = (180/pi)*atan2(vAveX, vAveY) - thetaA;
  thetaA += sampA*gammaA / fs;

  // Adjust thetaB
  double gammaB = 90 - (thetaB + (180/pi)*atan2(vAveX, vAveY));
  thetaB += sampB*gammaB / fs;

  // Adjust thetaC
  double gammaC = 90 - (thetaC + (180/pi)*atan2(vAveX, vAveY));
  thetaC += sampC*gammaC / fs;

  motorA.write(thetaA);
  motorB.write(thetaB);
  motorC.write(thetaC);
  //motorA.write(0);
  //motorB.write(0);
  //motorC.write(0);

  int pixelX = (int)(x * 32.0 / L);
  int pixelY = (int)(y * 32.0 / L);
  float velX = (float)(vAveX * 32.0 / L);
  float velY = (float)(vAveY * 32.0 / L);

  mySerial.println(pixelX);
  mySerial.println(pixelY);
  mySerial.println(velX);
  mySerial.println(velY);

  Serial.print("A: ");
  Serial.println(sampA);

  Serial.print("B: ");
  Serial.println(sampB);

  Serial.print("C: ");
  Serial.println(sampC);

  Serial.println();

  delay(1000 / fs);
  
}




















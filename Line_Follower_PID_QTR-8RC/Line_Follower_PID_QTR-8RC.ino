//Started: 20/04/2023, updated: 03/05/2023
//Author: Andrew Kennedy
//Line Follower PID with the Pololu QTR-8RC sensor

//------------------PID Control-------------------
float Kp=1;
float Ki=0.002;
float Kd=1.5;

const byte maxSpeed = 255; 
bool isLineBlack = true;
byte calibTime = 3; //Calibration time in seconds
//-------------------------------------------------

#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

//H Bridge          [ENA~,IN1,IN2,IN3,IN4,ENB~]
const byte hBridge[] = {10,A0,A1,A2,A3,11};

float P=0, I=0, D=0, PID=0, error=0, lastError=0;
int lSpeed, rSpeed;

void setup() {
  Serial.begin(9600);

  //Configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount);
  calibration();
}

void loop() {
  //Read sensors
  error = map(readSensors(), 0, 7000, -1000, 1000);

  //Calculate PID
  P = error;
  I = I + error;
  D = error - lastError;
  PID = (Kp*P) + (Ki*I) + (Kd*D);
  lastError = error;

  //Control Motors
  lSpeed = maxSpeed + PID;
  rSpeed = maxSpeed - PID;

  lSpeed = constrain(lSpeed, -maxSpeed, maxSpeed);
  rSpeed = constrain(rSpeed, -maxSpeed, maxSpeed);
  forwardOverride(20);

  speed(lSpeed, rSpeed);
}
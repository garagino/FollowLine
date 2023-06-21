/****************************************************************
* Started     : 20/Apr/2023
* updated     : 11/May/2023
* Author      : Andrew Kennedy
* Description : Line Follower PID with the Pololu QTR-8RC sensor
*               and serial communication for wireless control.                       
****************************************************************/
#include "Variables.h"

//------------------PID Control------------------- 
float Kp=1.5;
float Ki=0.002;
float Kd=1.5;

byte maxSpeed = 255; 
bool line = black;
//-------------------------------------------------

void setup() {
  BtSerial.begin(9600);
  delay(50);
  sensorSetup();
  calibration(3, false); //In seconds
  pinMode(markerSensorPin, INPUT);
  PIDnow(5); //Print PID values
}

void loop() {
  //Communicate with PC or wireless
  Parser(serialConnection());

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
  
  //check the markers
  markerChecker();
}
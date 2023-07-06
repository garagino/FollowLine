/****************************************************************
* Started     : 03/Jul/2023
* updated     : 03/Jul/2023
* Author      : Luiz Eduardo
* Description : A Script to test the components for the project.               
****************************************************************/
#include "Variables.h"

//------------------PID Control------------------- 

//-------------------------------------------------

void setup() {
  delay(50);
  sensorSetup();
  pinMode(auxSensorPin, INPUT);
  Serial.begin(9600);//arduino
  //Serial.begin(115200);//vespa
}

void loop() {
  //testReadSensorsMain();
  //testReadSensorsAux();
  //test_motor_single(int motorPinIn, int motorPinOut);
  //test_motor_integrated_arduino(1,1);
  //test_motor_integrated_vespa();
  //test_battery_vespa();
}

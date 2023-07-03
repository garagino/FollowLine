/****************************************************************
* Started     : 03/Jul/2023
* updated     : 03/Jul/2023
* Author      : Luiz Eduardo
* Description : A Script to test the components for the project.               
****************************************************************/
#include "Variables.h"

//------------------PID Control------------------- 

bool line = white;
//-------------------------------------------------

void setup() {
  delay(50);
  sensorSetup();
  pinMode(auxSensorPin, INPUT);
}

void loop() {
}
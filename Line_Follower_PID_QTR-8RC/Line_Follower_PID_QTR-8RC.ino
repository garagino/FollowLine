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
  Serial.begin(9600);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte choice = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(choice, DEC);

}
}
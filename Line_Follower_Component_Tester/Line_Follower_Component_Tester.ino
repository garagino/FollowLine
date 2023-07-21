/****************************************************************
* Started     : 03/Jul/2023
* updated     : 03/Jul/2023
* Author      : Luiz Eduardo
* Description : A Script to test the components for the project.               
****************************************************************/
#include <RoboCore_Vespa.h>  // Library for the Vespa microcontroller
#include <QTRSensors.h>      // Library for the QTR-8A or the QTR-8RC

VespaMotors motor;         // Vespa Motor Object
QTRSensors qtr;            // QTR Sensor

// Set button and led pins
const uint8_t PIN_BUTTON = 35;
const uint8_t PIN_LED = 15;
const uint8_t PIN_MARKER_SENSOR = 36;

// delays values
const int Setup_Delay=100;
const int auxSensorTest_Delay

//setup
const int Begin_value=115200;

const int PAUSE_TIME = 3000;
long speed = 100; 

//Setup of the module of sensors
const uint8_t SENSOR_COUNT = 8;       // The number of sensors, which should match the length of the pins array
const uint8_t[] QTR_8RC={ 17, 16, 18, 5, 23, 19, 22, 21 }
uint16_t sensorValues[SENSOR_COUNT];  // An array in which to store the calibrated sensor readings

//Motor turning values
const int Motor_Turn1 = 90;
const int Motor_Turn2 = 30;


void setup() {
  Serial.begin(Begin_value);
  delay(Setup_Delay);

  qtr.setTypeRC();  // For QTR-8RC      Sensor pins:
  qtr.setSensorPins(QTR_8RC, SENSOR_COUNT);

  pinMode(PIN_MARKER_SENSOR, INPUT);
}

void loop() {
  mainSensorTest();
  //auxSensorTest();
  //vespaTestMotors();
}

void auxSensorTest(){
  delay(auxSensorTest_Delay);
  Serial.println(digitalRead(PIN_MARKER_SENSOR));
  Serial.println(analogRead(PIN_MARKER_SENSOR));
}


void mainSensorTest(){
  
  // read raw sensor values
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SENSOR_COUNT; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.println();
}

void vespaTestMotors(){
  Serial.println("Forward");
  motor.forward(speed);
  delay(PAUSE_TIME);
  motor.stop();
  
  Serial.println("Backward");
  motor.backward(speed);
  delay(PAUSE_TIME);
  motor.stop();
  
  Serial.println("Left 1");
  motor.setSpeedLeft(speed);
  delay(PAUSE_TIME);
  motor.stop();
  Serial.println("Left 2");
  motor.setSpeedLeft(-speed);
  delay(PAUSE_TIME);
  motor.stop();
  
  Serial.println("Right 1");
  motor.setSpeedRight(speed);
  delay(PAUSE_TIME);
  motor.stop();
  Serial.println("Right 2");
  motor.setSpeedRight(-speed);
  delay(PAUSE_TIME);
  motor.stop();
  
  Serial.println("Turn");
  motor.turn(Motor_Turn1,Motor_Turn2);
  delay(PAUSE_TIME);
  motor.stop();
  
  delay(PAUSE_TIME);
}

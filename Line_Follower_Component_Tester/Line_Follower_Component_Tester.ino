/****************************************************************
* Started     : 03/Jul/2023
* updated     : 03/Jul/2023
* Author      : Luiz Eduardo
* Description : A Script to test the components for the project.               
****************************************************************/

#include <RoboCore_Vespa.h>  // Library for the Vespa microcontroller
#include <QTRSensors.h>      // Library for the QTR-8A or the QTR-8RC

VespaMotors motor;  // Vespa Motor Object
QTRSensors qtr;     // QTR Sensor

// Set button and led pins
const uint8_t PIN_BUTTON = 35;
const uint8_t PIN_LED = 15;
const uint8_t PIN_MARKER_SENSOR = 36;

const int PAUSE_TIME = 3000;
long speed = 100;

//Setup of the module of sensors
const uint8_t SENSOR_COUNT = 8;       // The number of sensors, which should match the length of the pins array
uint16_t sensorValues[SENSOR_COUNT];  // An array in which to store the calibrated sensor readings

void setup() {
  Serial.begin(115200);
  delay(100);

  qtr.setTypeRC();  // For QTR-8RC      Sensor pins:
  qtr.setSensorPins((const uint8_t[]){ 21, 19, 5, 16, 22, 23, 18, 17 }, SENSOR_COUNT);

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_MARKER_SENSOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  mainSensorTest();
  //auxSensorTest();
  //vespaTestMotors();
}

void auxSensorTest() {
  Serial.print("D: ");
  Serial.println(digitalRead(PIN_MARKER_SENSOR));
  Serial.print("\tA: ");
  Serial.println(analogRead(PIN_MARKER_SENSOR));
  delay(250);
}

void mainSensorTest() {
  // read raw sensor values
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.println();
}

void vespaTestMotors() {
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
  motor.turn(90, 30);
  delay(PAUSE_TIME);
  motor.stop();

  delay(PAUSE_TIME);
}

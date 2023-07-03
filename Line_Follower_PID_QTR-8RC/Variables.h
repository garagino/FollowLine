#include <QTRSensors.h> //Library for the QTR-8A or the QTR-8RC
QTRSensors qtr;

//Define the values of lines in sensors:
#define black 0
#define white 1

//Test variables
const unsigned long testDelay = 3000;
long currentTimeTest = 0;

//Auxiliary Sensor variables
const int auxSensorPin = 12; //we gotta change that

//Setup of the module array of sensors(Main Sensor):
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
void sensorSetup() {
  qtr.setTypeRC(); //                Sensor pins:
  qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount);
}

//Setup of the module that control the motors:
//H Bridge          [ENA~,IN1,IN2,IN3,IN4,ENB~]
const byte hBridge[] = {10,A0,A1,A2,A3,11};




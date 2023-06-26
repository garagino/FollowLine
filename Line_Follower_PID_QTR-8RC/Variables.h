#include <QTRSensors.h> //Library for the QTR-8A or the QTR-8RC
QTRSensors qtr;

//Setup of the module array of sensors:
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
void sensorSetup() {
  qtr.setTypeRC(); //                Sensor pins:
  qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount);
}

//Setup of the module that control the motors:
//H Bridge          [ENA~,IN1,IN2,IN3,IN4,ENB~]
const byte hBridge[] = {10,A0,A1,A2,A3,11};

#define black 0
#define white 1

float P=0, I=0, D=0, PID=0, error=0, lastError=0;
int lSpeed, rSpeed;

bool robotRun = false;

//Software serial setup
#include <SoftwareSerial.h>

#define rxPin 10 //input pin
#define txPin 11 //output pin

SoftwareSerial BtSerial =  SoftwareSerial(rxPin, txPin);

//Marker sensor variables
int markerCount = 62;//maker total of actual track
const int markerSensorPin = 12; //we gotta change that
bool markerDetected = false;
unsigned long markerDetectionTime = 0;
const unsigned long markerDelay = 100;

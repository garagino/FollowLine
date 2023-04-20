//Data de início: 20/04/2023
//Autor: Andrew Kennedy
//Seguidor de linha PID utilizando o sensor Pololu QTR-8RC

#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

float error=0, P=0, I=0, D=0, PID=0;
float prevError=0, prevI=0;
uint16_t position = 0;
const byte initial_motor_speed = 180; 

//PID Control
float Kp=4;
float Ki=0.002;
float Kd=2;

//H Bridge       [ENA~,IN1,IN2,IN3,IN4,ENB~]
const byte h[] = {10,A0,A1,A2,A3,11};

void setup()
{
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount);

//Calibration---------------------------------
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
//----------------------------------------------


  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
}

void loop() {
  //Read sensors
  position = qtr.readLineBlack(sensorValues);
  error = map(position, 0, 7000, -100, 100);

  //Calculate PID
  P = error;
  I = I + error;
  D = error-prevError;
  PID = (Kp*P) + (Ki*I) + (Kd*D);
  prevError = error;

  //Control Motors
  int left_motor_speed = initial_motor_speed + PID;
  int right_motor_speed = initial_motor_speed - PID;

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  speed(left_motor_speed, right_motor_speed);
}
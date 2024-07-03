/****************************************************************
* Folow Line
* CESAR School
* 
* Line Follower PID with the microcontroller Vespa 
* from RoboCore and the Pololu's QTR-8RC sensor
****************************************************************/

#define DEBUG
#define BT_NAME "vin-A"
// Names: Mutuca | Motoneta | Van Dyne


#ifdef DEBUG
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;  // Bluetooth Serial instance
#endif

#include <RoboCore_Vespa.h>  // Library for the Vespa microcontroller
#include <QTRSensors.h>      // Library for the QTR-8A or the QTR-8RC

VespaMotors motor;  // Vespa Motor  Object
QTRSensors qtr;     // QTR Sensor

// Set button and led pins
const uint8_t PIN_BUTTON = 35;
const uint8_t PIN_LED = 15;
const uint8_t PIN_MARKER_SENSOR = 36;

//Setup of the module of sensors
const uint8_t SENSOR_COUNT = 8;       // The number of sensors, which should match the length of the pins array
uint16_t sensorValues[SENSOR_COUNT];  // An array in which to store the calibrated sensor readings

// Maximum line position, considering the amount of sensors.
const long MAX_POSITION = (SENSOR_COUNT - 1) * 1000;

//Marker sensor variables
unsigned long startMakerChecker = 35500L;
unsigned long initialTime;

//Curve Break variables
unsigned long startCurveBreak;
bool curveBreak = false;

// Limit value of the margin of error
int marginError = 20;

bool firstRun = true;

//------------------PID Control-------------------
float p = 0, i = 0, d = 0, pid = 0, error = 0, lastError = 0;

float Kp = 0.71;
float Ki = 0.0001;
float Kd = 4.3;

int turnSpeed = 100;

int maxSpeed = 100;
int integralLimit = 200;
int lSpeed, rSpeed;

const bool LINE_BLACK = false;

bool limiter = true;

//------------------Encoder-------------------

float distanceLeftMotor;
float distanceRightMotor;
float distance = 565;
float distanceAverage;
float multEncoder;
 




// Todas as portas da esp32 suportam interrupt, estou chutando que essas portas vão funcionar
int encoderLeftPin1 = 25; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderLeftPin2 = 26; //Encoder Output 'B' must connected with intreput pin of arduino.

int encoderRightPin1 = 33; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderRightPin2 = 32; //Encoder Output 'B' must connected with intreput pin of arduino.


volatile int lastEncodedLeft = 0; // Here updated value of encoder store.
volatile int lastEncodedRight = 0; // Here updated value of encoder store.

volatile long encoderValueLeft = 0; // Raw encoder value
volatile long encoderValueRight = 0; // Raw encoder value

//-------------------------------------------------

void setup() {
  qtr.setTypeRC();  // For QTR-8RC      Sensor pins:
  qtr.setSensorPins((const uint8_t[]){ 21, 19, 5, 16, 22, 23, 18, 17 }, SENSOR_COUNT);

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_MARKER_SENSOR, INPUT);
  pinMode(PIN_LED, OUTPUT);

  multEncoder = 0.0526;

  pinMode(encoderLeftPin1, INPUT_PULLUP); 
  pinMode(encoderLeftPin2, INPUT_PULLUP);

  pinMode(encoderRightPin1, INPUT_PULLUP); 
  pinMode(encoderRightPin2, INPUT_PULLUP);

  digitalWrite(encoderLeftPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderLeftPin2, HIGH); //turn pullup resistor on

  digitalWrite(encoderRightPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderRightPin2, HIGH); //turn pullup resistor on

  pinMode(PIN_MARKER_SENSOR, INPUT);

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  attachInterrupt(PIN_MARKER_SENSOR, curveBreaker, RISING);



#ifdef DEBUG
  if (firstRun) {
    Serial.begin(115200);
    delay(100);

    SerialBT.begin(BT_NAME);  // Bluetooth device name
    firstRun = false;
  }

  SerialBT.println("Start BT communication");

  String btMessage;
  String prefix;

  while (prefix != "end" && digitalRead(PIN_BUTTON) == HIGH) {
    btMessage = receiveBtMessage();
    prefix = getPrefix(btMessage);

    if (prefix == "turn") {
      turnSpeed = getNumber(btMessage, 1);
    }

    if (prefix == "pid") {
      Kp = getNumber(btMessage, 1);
      Ki = getNumber(btMessage, 2);
      Kd = getNumber(btMessage, 3);
    } else if (prefix == "spe") {
      maxSpeed = getNumber(btMessage, 1);
    } else if (prefix == "turn") {
      turnSpeed = getNumber(btMessage, 1);
    } else if (prefix == "tim") {
      startMakerChecker = getNumber(btMessage, 1);
    } else if (prefix == "err") {
      marginError = getNumber(btMessage, 1);
    } else if (prefix == "dis") {
      distance = getNumber(btMessage, 1);
    } else if (prefix == "mul") {
      multEncoder = getNumber(btMessage, 1);
    } else if (prefix == "pri") {
      printParameters();
    } else if (prefix == "end") {
      break;
    } else if (prefix == "lim"){
      if ( limiter == false){
        limiter = true;
        SerialBT.println("Limiter ativado!");
      } else{
        limiter = false;
        SerialBT.println("Limiter desativado!");
      }
    } else {
      SerialBT.println("This command doesn't exists!");
    }
  }

  printParameters();

  SerialBT.println("Start Calibration...");

  delay(500);
#endif

  // Calibration
  digitalWrite(PIN_LED, HIGH);
  while (digitalRead(PIN_BUTTON) == HIGH) {  // Calibrates until the button is pressed
    Serial.print("Left  ");
    Serial.print(distanceLeftMotor);
    Serial.print("  ");
    Serial.print("Right  ");
    Serial.println(distanceRightMotor);

 

    qtr.calibrate();

    encoderValueLeft = 0;
    encoderValueRight = 0;

  }
  digitalWrite(PIN_LED, LOW);

#ifdef DEBUG
  // Print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    SerialBT.print(qtr.calibrationOn.minimum[i]);
    SerialBT.print(' ');
  }
  SerialBT.println();

  // Print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    SerialBT.print(qtr.calibrationOn.maximum[i]);
    SerialBT.print(' ');
  }
  SerialBT.println();
#endif

  delay(2000);  // Start loop after 2 seconds
  initialTime = millis();
}

void loop() {
  // readSensors() returns the line position between 0 and `MAX_POSITION`.
  // error is a re-map from -1000 to 1000 range.

  Serial.print("Left  ");
  Serial.print(distanceLeftMotor);
  Serial.print("  ");
  Serial.print("Right  ");
  Serial.println(distanceRightMotor);

  error = map(readSensors(), 0, MAX_POSITION, -1000, 1000);





  // Calculate PID
  p = error;
  i = i + error;
  if (limiter == true){
    i = constrain(i, -integralLimit, integralLimit); // Limita o valor do integral
  }
  d = error - lastError;
  pid = (Kp * p) + (Ki * i) + (Kd * d);
  lastError = error;

  // Control Motors
  lSpeed = maxSpeed + pid;
  rSpeed = maxSpeed - pid;

  lSpeed = constrain(lSpeed, -maxSpeed, maxSpeed);
  rSpeed = constrain(rSpeed, -maxSpeed, maxSpeed);


  updateEncoder();


  if (markerChecker()) {  // Count the markers and stop the robot when reach a certain number
    SerialBT.print("Left  ");
    SerialBT.print(distanceLeftMotor);
    SerialBT.print("  ");
    SerialBT.print("Right  ");
    SerialBT.println(distanceRightMotor);
    motor.stop();



#ifdef DEBUG
    SerialBT.print(">> Timelapse: "); 
    SerialBT.print(millis() - initialTime);
    SerialBT.println(" seconds");
#endif
    setup();
  } else if (error >= -marginError && error <= marginError) {  // If the error is within the MARGIN_ERROR, move on
    motor.turn(turnSpeed, turnSpeed);
  } else {  // If the error is outside the error range, continue doing PID
    motor.turn(lSpeed, rSpeed);
  }else if (curveBreak){
    if (millis() - startCurveBreak > 100) curveBreak = false;
    motor.stop();
  }
}

int readSensors() {
  if (LINE_BLACK) {
    return qtr.readLineBlack(sensorValues);
  } else {
    return qtr.readLineWhite(sensorValues);
  }
}

/**
  Verifies if there is a end line after a set time

  @return `true` if the end line was detected.
*/
bool markerChecker() {

  distanceLeftMotor = encoderValueLeft*multEncoder;
  distanceRightMotor = encoderValueRight*multEncoder;

  distanceAverage = (distanceLeftMotor/2.0) + (distanceRightMotor/2.0);

  static int i = 0;
  if (startMakerChecker < millis() - initialTime) {
    // if (analogRead(PIN_MARKER_SENSOR) < 2000) {
    return true;
    // }
  }
  if (distanceAverage > distance) {
    return true;
  }

  return false;
}

#ifdef DEBUG

/**
  Returns all stream of data sent over bluetooth until the
  button is pressed.

  @return `String` with the message sent by the bluetooth device
*/
String receiveBtMessage() {
  String message;
  char incomingChar;

  digitalWrite(PIN_LED, HIGH);
  while (digitalRead(PIN_BUTTON) == HIGH) {
    if (SerialBT.available()) {
      incomingChar = SerialBT.read();

      if (incomingChar == '\n') break;

      message += String(incomingChar);
    }
  }
  digitalWrite(PIN_LED, LOW);

  message.trim();
  return message;
}

String getPrefix(String data) {
  return getElement(data, 0);
}

double getNumber(String data, int index) {
  return atof(getElement(data, index).c_str());
}

/**
  Returns a sub-string in the `String` data, in the index
  position.

  @param `data` String with the message
  @param `index` Position of the element to be returned
  @return `String` sub-string in the indicated position. If there is
  no value at this position, it returns empty string.
*/
String getElement(String data, int index) {
  char separator = ' ';
  int found = 0;
  int startIndex = 0, endIndex = -1;
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      startIndex = endIndex + 1;
      endIndex = (i == maxIndex) ? i + 1 : i;
    }
  }

  if (found <= index) {
    return "";
  }

  return data.substring(startIndex, endIndex);
}

void printParameters() {
  SerialBT.println("Configured parameters:");
  SerialBT.print(">> P: ");
  SerialBT.print(Kp, 4);
  SerialBT.print(" | I: ");
  SerialBT.print(Ki, 4);
  SerialBT.print(" | Kd: ");
  SerialBT.println(Kd, 4);

  SerialBT.print(">> Speed: ");
  SerialBT.println(maxSpeed);

  SerialBT.print(">> Time delay: ");
  SerialBT.println(startMakerChecker);

  SerialBT.print(">> Margin Error: ");
  SerialBT.println(marginError);

  SerialBT.print(">> Limitador: ");
  SerialBT.println(limiter);

  SerialBT.print(">> turnSpeed: ");
  SerialBT.println(turnSpeed);

  SerialBT.print(">> Distance: ");
  SerialBT.println(distance);
  SerialBT.print(">> Mult Encoder: ");
  SerialBT.println(multEncoder);
}

#endif



void updateEncoder(){

  /*************************************************
  circuferencia levando pi a 5 casas=
  188.4954

  Pontos por mm: 
  72.27232070384741
  



  **************************************************/
  int MSB = digitalRead(encoderLeftPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderLeftPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting thex 2 pin value to single number
  int sum  = (lastEncodedLeft << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueLeft --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueLeft ++;

  lastEncodedLeft = encoded; //store this value for next time

  MSB = digitalRead(encoderRightPin1); //MSB = most significant bit
  LSB = digitalRead(encoderRightPin2); //LSB = least significant bit

  encoded = (MSB << 1) |LSB; //converting thex 2 pin value to single number
  sum  = (lastEncodedRight << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueRight --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueRight ++;

  lastEncodedRight = encoded; //store this value for next time


}

void curveBreaker (){

  startCurveBreak = millis();
  curveBreak = true;

}
void WaitingTest(int starTimeTest){
while(starTimeTest - currentTimeTest >= testDelay){
currentTimeTest = millis();
}
}


void test_motor_integrated() {
  int directionL;
  int directionR;
  
  directionL = 1;
  directionR = 1;
  speed(directionL,directionR);
  WaitingTest(millis());

  directionL = -1;
  directionR = -1;
  speed(directionL,directionR);
  WaitingTest(millis());

  directionL = 1;
  directionR = -1;
  speed(directionL,directionR);
  WaitingTest(millis());

  directionL = -1;
  directionR = 1;
  speed(directionL,directionR);
  WaitingTest(millis());

}


void test_motor_single(int motorPinIn, int motorPinOut) {
  
  digitalWrite(motorPinIn, HIGH);
  digitalWrite(motorPinOut, LOW);
  WaitingTest(millis());

  digitalWrite(motorPinIn, LOW);
  digitalWrite(motorPinOut, HIGH);
  WaitingTest(millis());
}


void speed(int mL, int mR) {
  analogWrite(hBridge[0], abs(mL));
  if(mL >=0) {
    digitalWrite(hBridge[1], HIGH);
    digitalWrite(hBridge[2], LOW);
  } else{
    digitalWrite(hBridge[1], LOW);
    digitalWrite(hBridge[2], HIGH);
  }
  analogWrite(hBridge[5], abs(mR));
  if(mR >=0) {
    digitalWrite(hBridge[3], HIGH);
    digitalWrite(hBridge[4], LOW);
  } else{
    digitalWrite(hBridge[3], LOW);
    digitalWrite(hBridge[4], HIGH);
  }
}


int testReadSensorsMain() {
  if(line == black) {
    return qtr.readLineBlack(sensorValues);
  }else{
    return qtr.readLineWhite(sensorValues);
  }
}

int testReadSensorsAux() {
  return digitalRead(auxSensorPin);
}



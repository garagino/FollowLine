void WaitingTest(int starTimeTest){
while(starTimeTest - currentTimeTest >= testDelay){
currentTimeTest = millis();
}
}


void test_motor_integrated() {
  int directionL;
  int directionR;
  Serial.println("Começando teste do Motor");
  
  directionL = 1;
  directionR = 1;
  speed(directionL,directionR);
  Serial.println("Motor rodando para frente");
  WaitingTest(millis());

  directionL = -1;
  directionR = -1;
  speed(directionL,directionR);
  Serial.println("Motor rodando para trás");
  WaitingTest(millis());

  directionL = 1;
  directionR = -1;
  Serial.println("Motor rodando para esquerda");
  speed(directionL,directionR);
  WaitingTest(millis());

  directionL = -1;
  directionR = 1;
  Serial.println("Motor rodando para direita");
  speed(directionL,directionR);
  WaitingTest(millis());

  Serial.println("Fim do Teste");
}


void test_motor_single(int motorPinIn, int motorPinOut) {
  
  Serial.println("Motor no sentido Horário");
  digitalWrite(motorPinIn, HIGH);
  digitalWrite(motorPinOut, LOW);
  WaitingTest(millis());

  Serial.println("Motor no sentido Anti-Horário");
  digitalWrite(motorPinIn, LOW);
  digitalWrite(motorPinOut, HIGH);
  WaitingTest(millis());

  Serial.println("Fim do teste");
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


void testReadSensorsMain() {
  if(line == black) {
    int values = qtr.readLineBlack(sensorValues);
    Serial.println("Main Sensor Values: ", values);
  }else{
    int values = qtr.readLineWhite(sensorValues);
    Serial.println("Main Values: ", values);
  }

  WaitingTest(millis());
}

void testReadSensorsAux() {
  int values = digitalRead(auxSensorPin);
  Serial.println("Aux Sensor Values: ", values);
  WaitingTest(millis());
}



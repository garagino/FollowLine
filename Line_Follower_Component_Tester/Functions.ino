void WaitingTest(int starTimeTest){
while(starTimeTest - currentTimeTest >= testDelay){
currentTimeTest = millis();
}
}


void test_motor_integrated_arduino(int directionL,int directionR) {
  // Frente(DL = 1, DR = 1)
  // Ré(DL = -1, DR = -1)
  // Esquerda(DL = 1, DR = -1)
  // Frente(DL = -1, DR = 1)

  speed(directionL,directionR);
  Serial.println("Motor rodando");
  WaitingTest(millis());
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
  analogWrite(hBridge[0], maxSpeed);
  if(mL >=0) {
    digitalWrite(hBridge[1], HIGH);
    digitalWrite(hBridge[2], LOW);
  } else{
    digitalWrite(hBridge[1], LOW);
    digitalWrite(hBridge[2], HIGH);
  }
  analogWrite(hBridge[5], maxSpeed);
  if(mR >=0) {
    digitalWrite(hBridge[3], HIGH);
    digitalWrite(hBridge[4], LOW);
  } else{
    digitalWrite(hBridge[3], LOW);
    digitalWrite(hBridge[4], HIGH);
  }
}


void testReadSensorsMain() {
  // read raw sensor values
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
}

void testReadSensorsAux() {
  int values = digitalRead(auxSensorPin);
  Serial.println("Aux Sensor Values: ");
  Serial.println(values);
  delay(250);
}

void test_motor_integrated_vespa(){

  Serial.println("Forward");
  motors.forward(100);
  delay(PAUSE_TIME);
  motors.stop();
  
  Serial.println("Backward");
  motors.backward(100);
  delay(PAUSE_TIME);
  motors.stop();
  
  Serial.println("Left 1");
  motors.setSpeedLeft(100);
  delay(PAUSE_TIME);
  motors.stop();
  Serial.println("Left 2");
  motors.setSpeedLeft(-100);
  delay(PAUSE_TIME);
  motors.stop();
  
  Serial.println("Right 1");
  motors.setSpeedRight(100);
  delay(PAUSE_TIME);
  motors.stop();
  Serial.println("Right 2");
  motors.setSpeedRight(-100);
  delay(PAUSE_TIME);
  motors.stop();
  
  Serial.println("Turn");
  motors.turn(90,30);
  delay(PAUSE_TIME);
  motors.stop();
  
  delay(PAUSE_TIME);
}

void test_battery_vespa(){
  Serial.print("Battery voltage: ");
  Serial.print(vbat.readVoltage());
  Serial.println(" mV");

  delay(1000);
}

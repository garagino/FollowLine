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

int readSensors() {
  if(isLineBlack) {
    return qtr.readLineBlack(sensorValues);
  }else{
    return qtr.readLineWhite(sensorValues);
  }
}

void printposition() {
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(readSensors());
}

void calibration() {
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH); //Turn on LED to indicate calibration

  while(millis() <= calibTime*1000) { 
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); 

  for (uint8_t i = 0; i < SensorCount; i++) // print the calibration minimum values
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t i = 0; i < SensorCount; i++)//Print the calibration maximum values 
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.println(' ');
  }
}

void forwardOverride(int margin) {
    if (error >= -margin and error <= margin) {
      lSpeed = maxSpeed;
      rSpeed = maxSpeed;
    }
  }
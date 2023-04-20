void speed(int mL, int mR) {
  analogWrite(h[0], abs(mL));
  if(mL >=0) {
    digitalWrite(h[1], HIGH);
    digitalWrite(h[2], LOW);
  } else{
    digitalWrite(h[1], LOW);
    digitalWrite(h[2], HIGH);
  }
  analogWrite(h[5], abs(mR));
  if(mR >=0) {
    digitalWrite(h[3], HIGH);
    digitalWrite(h[4], LOW);
  } else{
    digitalWrite(h[3], LOW);
    digitalWrite(h[4], HIGH);
  }
}

void printposition() {
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
}
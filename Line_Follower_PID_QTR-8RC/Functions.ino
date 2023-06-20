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
  if(line == black) {
    return qtr.readLineBlack(sensorValues);
  }else{
    return qtr.readLineWhite(sensorValues);
  }
}

void printposition() {
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    BtSerial.print(sensorValues[i]);
    BtSerial.print('\t');
  }
  BtSerial.println(readSensors());
}

void calibration(byte calibTime, bool prnt) {
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH); //Turn on the builtin LED to indicate calibration

  while(millis() <= calibTime*1000) { 
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); 

  if(prnt) {
    BtSerial.println("Calibration values: ");
    BtSerial.print("Minimum: ");
    for (uint8_t i = 0; i < SensorCount; i++) // print the calibration minimum values
    {
      BtSerial.print(qtr.calibrationOn.minimum[i]);
      BtSerial.print(' ');
    }
    BtSerial.println();

    BtSerial.print("Maximum: ");
    for (uint8_t i = 0; i < SensorCount; i++)//Print the calibration maximum values 
    {
      BtSerial.print(qtr.calibrationOn.maximum[i]);
      BtSerial.print(' ');
    }
    BtSerial.println("\n");
  }
}

void forwardOverride(int margin) {
    if (error >= -margin and error <= margin) {
      lSpeed = maxSpeed;
      rSpeed = maxSpeed;
    }
  }

void PIDnow(byte precision) {//-------------------------------------------------------------------
  BtSerial.println("PID(" + String(Kp, precision) + ", " + String(Ki, precision) + ", " + String(Kd, precision) + ")");
}

String serialConnection() {
  String out;
  static String s;
  static char c;
  if(BtSerial.available()) {
    c = BtSerial.read();
    if(c != '\n') s += c;
    else {
      out = s; 
      s = ""; 
      return out;
      }
  }
}

void Parser(String s) {
  if (s == "") return;
  s.replace(" ", ""); //Remove all spaces
  s.toLowerCase();
  int a = s.indexOf("=");

       if(s == "run")  robotRun = true;
  else if(s == "stop") stopRobot();
  else if(s == "line") line = !line;

  else if(a != -1) {
    //Separate things
    String x = s.substring(0, a); //Variable
    String y = s.substring(a+1, s.length()); //Value

    if(!isNumber(y)) {printError(2); return;}

    //Check variables
         if(x == "p") Kp = y.toFloat();
    else if(x == "i") Ki = y.toFloat();
    else if(x == "d") Kd = y.toFloat();
    else if(x == "speed") {
      maxSpeed = y.toInt();
      BtSerial.println("maxSpeed: " + String(y));
      return;
      }
    else{printError(1); return;};
    PIDnow(5);
  }else{
    printError(1);
  }
}

bool isNumber(String str) {
  bool hasDecimal = false;
  for (int i = 0; i < str.length(); i++) {
    char d = str.charAt(i);
    if (d == '.') {
      if (hasDecimal) {
        return false; // multiple decimal points
      }
      hasDecimal = true;
    } else if (!isdigit(d)) {
      return false; // non-digit character
    }
  }
  return true;
}

void printError(byte n) {
  if(n == 1) {
    BtSerial.println("Unknown Command.");
  }

  if( n == 2) {
    BtSerial.println("The value is not a number.");
  }
}

void stopRobot() {
  speed(0,0);
  BtSerial.println("Stop robot.");

  while(!robotRun) {
    Parser(serialConnection());
  }

  robotRun = false;
  BtSerial.println("Run robot.");
  speed(maxSpeed,maxSpeed);
  delay(100);
}
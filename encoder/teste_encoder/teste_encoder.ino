#include <RoboCore_Vespa.h>
VespaMotors motors;





float distanceLeftMotor;
float distanceRightMotor;

// Todas as portas da esp32 suportam interrupt, estou chutando que essas portas vão funcionar
int encoderLeftPin1 = 25; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderLeftPin2 = 26; //Encoder Output 'B' must connected with intreput pin of arduino.

int encoderRightPin1 = 33; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoderRightPin2 = 32; //Encoder Output 'B' must connected with intreput pin of arduino.


volatile int lastEncodedLeft = 0; // Here updated value of encoder store.
volatile int lastEncodedRight = 0; // Here updated value of encoder store.

volatile long encoderValueLeft = 0; // Raw encoder value
volatile long encoderValueRight = 0; // Raw encoder value


void setup() {
  

  Serial.begin(115200); //initialize serial comunication

  pinMode(encoderLeftPin1, INPUT_PULLUP); 
  pinMode(encoderLeftPin2, INPUT_PULLUP);

  pinMode(encoderRightPin1, INPUT_PULLUP); 
  pinMode(encoderRightPin2, INPUT_PULLUP);



  digitalWrite(encoderLeftPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderLeftPin2, HIGH); //turn pullup resistor on

  digitalWrite(encoderRightPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderRightPin2, HIGH); //turn pullup resistor on



  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  


}

void loop() {


  if (distanceRightMotor < 999.9){

  motors.forward(100);
  Serial.print("Left  ");
  Serial.print(distanceLeftMotor);
  Serial.print("  ");
  Serial.print("Right  ");
  Serial.println(distanceRightMotor);

}
  if (distanceRightMotor > 999.9){
    motors.stop();
    }
  Serial.print("Left  ");
  Serial.print(distanceLeftMotor);
  Serial.print("  ");
  Serial.print("Right  ");
  Serial.println(distanceRightMotor);
// for (int i = 0; i <= 500; i++){
// motors.backward(100);  
// Serial.print("Reverse  ");
// Serial.println(encoderValue);
// }

// delay(1000);

} 

void updateEncoder(){

  /*************************************************
  30 ticks == 100 mm
  
  pontos por volta: 
  301
    **************************************************/
  //Converting interruptions to mm: 188.4954 / 0,6283

  float conv; 
  conv = 188.4954/0.6283;
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

  distanceLeftMotor = encoderValueLeft*3.33;
  distanceRightMotor = encoderValueRight*3.33;
}

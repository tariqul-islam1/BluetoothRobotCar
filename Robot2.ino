#include <Servo.h>

// Movement
int minDistance = 10;

// Servo -----------------
Servo servo;
int servoPos = 0;
int servoPosMin = 0;
int servoPosMax = 180;

// Sonar -----------------
const int servoTrig = 10;
const int servoEcho = 11;

// motors
int ena = 3;
int enb = 9;
int in1 = 5;
int in2 = 6;
int in3 = 7;
int in4 = 8;
int defaultSpeed = 70;

void motorsSetup(){
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void left(int speed = defaultSpeed){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speed);
}

void right(int speed = defaultSpeed){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, speed);
}

void front(int speed = defaultSpeed){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void motorTest(){
  left();
  delay(2000);
  analogWrite(ena, 0);
  delay(2000);
  right();
  delay(2000);
  analogWrite(enb, 0);
  delay(2000);
  front();
  delay(2000);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
  delay(2000);
}

// SONAR CONTROL --------------------------------------------------------------------------------
int readSonar(){
  digitalWrite(servoTrig, LOW);
   //delayMicroseconds(1);
   digitalWrite(servoTrig, HIGH);
   delayMicroseconds(20);
   digitalWrite(servoTrig, LOW);
   return microsecondsToCentimeters(pulseIn(servoEcho, HIGH));
}

void printSonar(int cm, int type = 0){
  Serial.print(cm);
  if(type == 0){
   Serial.print("cm");
  }else{
    Serial.print("cm in while");
  }
   Serial.println();
}

int getDistance() {
  int cm = readSonar();
  if(cm > 200){
    cm = 100;
  }
  cm = map(cm, 5, 100, 0, 255);
  printSonar(cm);
  return cm;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

// SERVO CONTROL --------------------------------------------------------------------------------
bool goLeft = false;

void servoLoop() {
  const int stepWidth = 10;
  if(servoPos >= servoPosMax && !goLeft){
    goLeft = true;
  }else if (servoPos <= servoPosMin && goLeft){
    goLeft = false;
  }
  if(goLeft){
    servo.write(servoPos -= stepWidth);
  }else{
    servo.write(servoPos += stepWidth);
  }
  delay(40);
} 

void runCar(){
  front(getDistance());
}

void setup() {
  Serial.begin(9600);
  motorsSetup();
}

void loop() {
  //motorTest();
  runCar();
  
}

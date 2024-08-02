#include <Servo.h>


const int motorMain = 3;
const int motorM1 = 5; // Left Front
const int motorM2 = 6; // Right Front
const int motorM3 = 7; // Left Rear
const int motorM4 = 8; // Right Rear
const int trigPin = 13;
const int echoPin = 12;
const int servoPin = 11;
const int STATE_ROT = 0;
const int STATE_FWD = 1;


Servo myServo;


long duration;
int distance;
int minDistance = 999;
int state = STATE_ROT;


void setminDistance(int d) {
  if (d<minDistance && d>10){
    minDistance=d;
    Serial.print("Set minDistance to ");
    Serial.print(minDistance);
    Serial.println(" cm");


  }
}


void rotateMotors() {
  digitalWrite(motorMain, HIGH);
  digitalWrite(motorM1, HIGH);
  digitalWrite(motorM2, HIGH);
  digitalWrite(motorM3, HIGH);
  digitalWrite(motorM4, LOW);
}


void setup() {
  pinMode(motorMain, OUTPUT);
  pinMode(motorM1, OUTPUT);
  pinMode(motorM2, OUTPUT);
  pinMode(motorM3, OUTPUT);
  pinMode(motorM4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  myServo.attach(servoPin);


  Serial.begin(9600);


  Serial.println("Setup Complete");
  delay(5000);


  rotateMotors();
  for (int i = 0; i<50; i++) {
    distance = measureDistance();
    setminDistance(distance);
    delay(40);
  }
  Serial.print("Min - ");
  Serial.print(minDistance);
  Serial.println("cm");
  Serial.println("Done Measuring");
}


void runMotors() {
  digitalWrite(motorMain, HIGH);
  digitalWrite(motorM1, HIGH);
  digitalWrite(motorM2, HIGH);
  digitalWrite(motorM3, HIGH);
  digitalWrite(motorM4, HIGH);
}


void backwardMotors() {
  digitalWrite(motorMain, HIGH);
  digitalWrite(motorM1, HIGH);
  digitalWrite(motorM2, HIGH);
  digitalWrite(motorM3, LOW);
  digitalWrite(motorM4, LOW);
}


void stopMotors() {
  digitalWrite(motorMain, LOW);
}




int measureDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  // Trigger the sensor by setting the trigPin high for 10 ms
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);


  // Calculate the distance
  distance = duration * 0.0344 / 2; // Distance in cm


  // Print distance to serial monitor
  /*
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/


  return distance;
}


void loop() {
  distance = measureDistance();
  Serial.println(distance);
  setminDistance(distance);
  if (distance <= 10) {
    Serial.println("End");
    stopMotors();
    delay(10);
    exit(0);
  }
  if (state == STATE_FWD1) {
    rotateMotors();
    delay(1035)
    stopMotors();
    state = STATE_FWD2;
  if (state == STATE_FWD2)
    Serial.println("Move Forward");
    runMotors();
  }
  if (state == STATE_ROT)  {
    Serial.println("Rotating");
    rotateMotors();
    if (distance <= minDistance + 4) {
        state = STATE_FWD1;
    }
  }
  digitalWrite(motorMain,HIGH);
  delay(12);
  digitalWrite(motorMain,LOW);
  delay(8);
}



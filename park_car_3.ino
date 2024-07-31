#include <Servo.h>

const int motorMain = 3;
const int motorM1 = 5; // Left Front
const int motorM2 = 6; // Right Front
const int motorM3 = 7; // Left Rear
const int motorM4 = 8; // Right Rear

const int trigPin = 13;
const int echoPin = 12;

const int servoPin = 11;

Servo myServo;

long duration;
int distance;
int minDistance = 999;

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
  delay(2000);
}

//needs fix
void rotateMotors() {
  digitalWrite(motorMain, HIGH);
  digitalWrite(motorM1, HIGH);
  analogWrite(motorM2, -150);
  digitalWrite(motorM3, HIGH);
  analogWrite(motorM4, -150);
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
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  return distance;
}

void loop() {
  if(distance > minDistance + 0.5 || distance < minDistance - 0.5) {
    distance = measureDistance();
    if(distance <= minDistance) {
      minDistance == distance;
    }
    rotateMotors();
    delay(100);
  }else {
    Serial.println("Found Minimum Distance")
    stopMotors();
    delay(10);
    while (measureDistance() > 4) {
      runMotors();
    }
  }
}
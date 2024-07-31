#include <Servo.h>

// 모터 제어 핀
const int motorMain =3;
const int motorM1 = 5; // Left Front
const int motorM2 = 6; // Right Front
const int motorM3 = 7; // Left Rear
const int motorM4 = 8; // Right Rear

// Ultrasonic 센서 핀
const int trigPin = 13; // Trigger 핀
const int echoPin = 12; // Echo 핀

// 서보 핀
const int servoPin = 11; // 서보 핀

// 서보 객체 생성
Servo myServo;

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(motorMain, OUTPUT);
  pinMode(motorM1, OUTPUT);
  pinMode(motorM2, OUTPUT);
  pinMode(motorM3, OUTPUT);
  pinMode(motorM4, OUTPUT);

  // Ultrasonic 센서 핀을 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // 서보 핀 설정
  myServo.attach(servoPin);

  // 시리얼 통신 시작
  Serial.begin(9600);

  Serial.println("Setup Complete");
}

void runMotors() {
  Serial.println("test");
  // 왼쪽 앞 바퀴와 왼쪽 뒤 바퀴를 모두 돌리기
  digitalWrite(motorMain, HIGH);
  digitalWrite(motorM1, HIGH);
  digitalWrite(motorM2, HIGH);
  digitalWrite(motorM3, HIGH);
  digitalWrite(motorM4, HIGH);
  // 오른쪽 앞 바퀴와 오른쪽 뒤 바퀴를 모두 돌리기

  // 모든 모터 정지
  //digitalWrite(motorMain, LOW);
  //delay(1000); // 1초 동안 정지

  Serial.println("Forward")
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
  Serial.println("Stop")
}

int calc_distance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor

    digitalWrite(trigPin, HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10); // keep the trigger "ON" for 10 ms to generate
             // pulse for 10 ms.

    digitalWrite(trigPin, LOW); // Turn off the pulse trigger to stop
                       // pulse generation

    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver

    long duration = pulseIn(echoPin, HIGH);

    Serial.print("Distance: ");
    //Serial.print(distance); // Print the output in serial monitor
    Serial.println(" cm");
    return duration * 0.0344 / 2; // Expression to calculate distance using time
}

void loop()
{
    if(calc_distance() < 4) {
      stopMotors();
    } else {
      runMotors();
    }
    delay(100);
}

#include <stdio.h>

// **01. 센서 설정 및 변수 선언

#define LEFT_MOTOR_PIN1 5  // 왼쪽 모터 핀 1
#define LEFT_MOTOR_PIN2 6  // 왼쪽 모터 핀 2
#define RIGHT_MOTOR_PIN1 9 // 오른쪽 모터 핀 1
#define RIGHT_MOTOR_PIN2 10 // 오른쪽 모터 핀 2

#define TRIG_PIN 11 // 초음파 센서 트리거 핀
#define ECHO_PIN 12 // 초음파 센서 에코 핀

// 로봇의 움직임을 제어하는 변수
int motorSpeed = 200; // 모터 속도
int turnDelay = 200; // 회전 지연 시간

// 초음파 센서로 측정된 거리
float distance;

// **02. 초음파 센서를 이용한 거리 측정 함수
float measureDistance() {
  digitaldWrite(TRIG_PIN, LOW);
  delayMicroseconds(2); // 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // 음속을 이용한 거리 계산

  return distance;
}

// **03. 모터 제어 함수
void moveForward() {
  analogWrite(LEFT_MOTOR_PIN1, motorSpeed);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, motorSpeed);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
}

void turnLeft() {
  analogWrite(LEFT_MOTOR_PIN1, 0);
  analogWrite(LEFT_MOTOR_PIN2, motorSpeed);
  analogWrite(RIGHT_MOTOR_PIN1, motorSpeed);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
  delay(turnDelay);
}

void turnRight() {
  analogWrite(LEFT_MOTOR_PIN1, motorSpeed);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, 0);
  analogWrite(RIGHT_MOTOR_PIN2, motorSpeed);
  delay(turnDelay);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_PIN1, 0);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, 0);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
}

// **04. 삼각형 주행 및 상대 로봇 탐색
void searchOpponent() {
  // 1. 초기 위치에서 왼쪽으로 회전하여 벽을 감지
  while (measureDistance() > 10) { // 벽과의 거리가 10cm 이상일 때까지 회전
    turnLeft();
  }

  // 2. 벽을 따라 직진 (삼각형의 첫 번째 변)
  while (measureDistance() < 20) { // 벽과의 거리가 20cm 미만일 때까지 직진
    moveForward();
    distance = measureDistance(); 
    if (distance < 10) { // 벽과 너무 가까워지면 왼쪽으로 조금 회전
      turnLeft(); 
      delay(50); 
    }
  }

  // 3. 오른쪽으로 회전 (삼각형의 두 번째 변)
  turnRight(); 
  delay(turnDelay * 2); // 첫 번째 변과 같은 각도만큼 회전

  // 4. 벽을 따라 직진 (삼각형의 세 번째 변)
  while (measureDistance() < 20) { // 벽과의 거리가 20cm 미만일 때까지 직진
    moveForward();
    distance = measureDistance();
    if (distance < 10) { // 벽과 너무 가까워지면 오른쪽으로 조금 회전
      turnRight();
      delay(50);
    }
  }

  // 5. 다시 왼쪽으로 회전하여 초기 방향으로 복귀
  turnLeft();
  delay(turnDelay * 2); // 첫 번째 변과 같은 각도만큼 회전
}
// **05. 상대 로봇 공격
void attackOpponent() {
  // 초음파 센서를 사용하여 상대 로봇과의 거리 측정
  distance = measureDistance(); 

  if (distance < 30 && distance > 5) { // 상대 로봇이 30cm 이내에 있으면
    moveForward(); // 전진하여 상대 로봇을 밀어냄
  } else {
    searchOpponent(); // 상대 로봇을 찾기 위해 삼각형 주행
  }
}

// **06. 


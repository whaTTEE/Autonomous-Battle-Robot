#include <stdio.h>

// **01. ���� ���� �� ���� ����

#define LEFT_MOTOR_PIN1 5  // ���� ���� �� 1
#define LEFT_MOTOR_PIN2 6  // ���� ���� �� 2
#define RIGHT_MOTOR_PIN1 9 // ������ ���� �� 1
#define RIGHT_MOTOR_PIN2 10 // ������ ���� �� 2

#define TRIG_PIN 11 // ������ ���� Ʈ���� ��
#define ECHO_PIN 12 // ������ ���� ���� ��

// �κ��� �������� �����ϴ� ����
int motorSpeed = 200; // ���� �ӵ�
int turnDelay = 200; // ȸ�� ���� �ð�

// ������ ������ ������ �Ÿ�
float distance;

// **02. ������ ������ �̿��� �Ÿ� ���� �Լ�
float measureDistance() {
  digitaldWrite(TRIG_PIN, LOW);
  delayMicroseconds(2); // 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // ������ �̿��� �Ÿ� ���

  return distance;
}

// **03. ���� ���� �Լ�
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

// **04. �ﰢ�� ���� �� ��� �κ� Ž��
void searchOpponent() {
  // 1. �ʱ� ��ġ���� �������� ȸ���Ͽ� ���� ����
  while (measureDistance() > 10) { // ������ �Ÿ��� 10cm �̻��� ������ ȸ��
    turnLeft();
  }

  // 2. ���� ���� ���� (�ﰢ���� ù ��° ��)
  while (measureDistance() < 20) { // ������ �Ÿ��� 20cm �̸��� ������ ����
    moveForward();
    distance = measureDistance(); 
    if (distance < 10) { // ���� �ʹ� ��������� �������� ���� ȸ��
      turnLeft(); 
      delay(50); 
    }
  }

  // 3. ���������� ȸ�� (�ﰢ���� �� ��° ��)
  turnRight(); 
  delay(turnDelay * 2); // ù ��° ���� ���� ������ŭ ȸ��

  // 4. ���� ���� ���� (�ﰢ���� �� ��° ��)
  while (measureDistance() < 20) { // ������ �Ÿ��� 20cm �̸��� ������ ����
    moveForward();
    distance = measureDistance();
    if (distance < 10) { // ���� �ʹ� ��������� ���������� ���� ȸ��
      turnRight();
      delay(50);
    }
  }

  // 5. �ٽ� �������� ȸ���Ͽ� �ʱ� �������� ����
  turnLeft();
  delay(turnDelay * 2); // ù ��° ���� ���� ������ŭ ȸ��
}
// **05. ��� �κ� ����
void attackOpponent() {
  // ������ ������ ����Ͽ� ��� �κ����� �Ÿ� ����
  distance = measureDistance(); 

  if (distance < 30 && distance > 5) { // ��� �κ��� 30cm �̳��� ������
    moveForward(); // �����Ͽ� ��� �κ��� �о
  } else {
    searchOpponent(); // ��� �κ��� ã�� ���� �ﰢ�� ����
  }
}

// **06. 


#include <IRremote.h>

const int MOTOR_PIN_A = 11; // ���� ���� - ��
const int MOTOR_PIN_B = 10; // ���� ���� +��
const int MOTOR_PIN_C = 6; // ���� ���� + ��
const int MOTOR_PIN_D = 5; // ���� ���� - ��
const int REMOTE_PIN = 3; // ���ܼ� ���� �� ��ȣ ����

IRrecv irrecv(REMOTE_PIN); // ���ܼ� ���� PIN ����
decode_results results; // ���ŵ� ���ܼ� ��ȣ ���� ����

void setup()
{
  irrecv.enableIRIn(); // ���ܼ� ���� Ȱ��ȭ
  pinMode(MOTOR_PIN_A, OUTPUT);
  pinMode(MOTOR_PIN_B, OUTPUT);
  pinMode(MOTOR_PIN_C, OUTPUT);
  pinMode(MOTOR_PIN_D, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); // ���ŵ� ��ȣ ���
    
    // ���ŵ� ��ȣ�� ���� ���� ����
    if(results.value == 0xFD8877) {
      moveForward(); // ����
    } else if(results.value == 0xFD9867) {
      moveBackward(); // ����
    } else if(results.value == 0xFD28D7) {
      turnLeft(); // ��ȸ��
    } else if(results.value == 0xFD6897) {
      turnRight(); // ��ȸ��
    } else {
      turnStop(); // ����
    }
    
    delay(30);
    irrecv.resume(); // ���� ��ȣ ���� �غ�
  }
}

void moveForward() { // ���� : ������ ȸ��
  analogWrite(MOTOR_PIN_A, 255);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 255);
  analogWrite(MOTOR_PIN_D, 0);
}

void moveBackward() { // ���� : ������ ȸ��
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 255);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 255);
}

void turnLeft() { // ��ȸ��
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 255);
  analogWrite(MOTOR_PIN_C, 255);
  analogWrite(MOTOR_PIN_D, 0);
}

void turnRight() { // ��ȸ��
  analogWrite(MOTOR_PIN_A, 255);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 255);
}

void turnStop() { // ����
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 0);
}

#include <NewPing.h>

// �� ����
#define TRIG_PIN_FRONT 7
#define ECHO_PIN_FRONT 6
#define IR_SENSOR_LEFT A0
#define IR_SENSOR_RIGHT A1
#define MOTOR_SPEED_MAX 255
#define MOTOR_SPEED_LOW (MOTOR_SPEED_MAX / 3)

// ������ ���� ����
#define MAX_DISTANCE 200
NewPing sonarFront(TRIG_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE);

// ���� ���� �Լ�
void setMotorSpeed(int speed) {
analogWrite(enablePinLeft, speed);
analogWrite(enablePinRight, speed);
}

// ȸ�� �Լ�
void rotateRight120() {
setMotorSpeed(MOTOR_SPEED_LOW)
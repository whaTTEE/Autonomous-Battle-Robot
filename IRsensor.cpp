#include <IRremote.h>

const int MOTOR_PIN_A = 11; // 좌측 모터 - 극
const int MOTOR_PIN_B = 10; // 좌측 모터 +극
const int MOTOR_PIN_C = 6; // 우측 모터 + 극
const int MOTOR_PIN_D = 5; // 우측 모터 - 극
const int REMOTE_PIN = 3; // 적외선 센서 핀 번호 정의

IRrecv irrecv(REMOTE_PIN); // 적외선 센서 PIN 매핑
decode_results results; // 수신된 적외선 신호 저장 변수

void setup()
{
  irrecv.enableIRIn(); // 적외선 센서 활성화
  pinMode(MOTOR_PIN_A, OUTPUT);
  pinMode(MOTOR_PIN_B, OUTPUT);
  pinMode(MOTOR_PIN_C, OUTPUT);
  pinMode(MOTOR_PIN_D, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); // 수신된 신호 출력
    
    // 수신된 신호에 따라 모터 동작
    if(results.value == 0xFD8877) {
      moveForward(); // 전진
    } else if(results.value == 0xFD9867) {
      moveBackward(); // 후진
    } else if(results.value == 0xFD28D7) {
      turnLeft(); // 좌회전
    } else if(results.value == 0xFD6897) {
      turnRight(); // 우회전
    } else {
      turnStop(); // 정지
    }
    
    delay(30);
    irrecv.resume(); // 다음 신호 수신 준비
  }
}

void moveForward() { // 전진 : 정방향 회전
  analogWrite(MOTOR_PIN_A, 255);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 255);
  analogWrite(MOTOR_PIN_D, 0);
}

void moveBackward() { // 후진 : 역방향 회전
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 255);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 255);
}

void turnLeft() { // 좌회전
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 255);
  analogWrite(MOTOR_PIN_C, 255);
  analogWrite(MOTOR_PIN_D, 0);
}

void turnRight() { // 우회전
  analogWrite(MOTOR_PIN_A, 255);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 255);
}

void turnStop() { // 정지
  analogWrite(MOTOR_PIN_A, 0);
  analogWrite(MOTOR_PIN_B, 0);
  analogWrite(MOTOR_PIN_C, 0);
  analogWrite(MOTOR_PIN_D, 0);
}

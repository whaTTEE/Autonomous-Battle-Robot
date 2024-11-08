#include <NewPing.h> 초음파센서 구동위한 라이브러리, 
//라이브러리 설치: 아두이노 IDE에서 Sketch > Include Library > Manage Libraries...로 가서 NewPing을 검색하여 설치

int time = 0;

int input = 0;

int distance = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  //트리거핀이 신호를 보내기 위해 설정
  digitalWrite(triggerPin, LOW); //전압이 0인 상태로 트리거핀을 초기화, 안정된 상태에서 신호를 받기 시작함
  delayMicroseconds(2); //아두이노 2마이크로초 동안 아무 작업 없이 대기. 신호의 안정성 높이기 위함
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() //시작할때 한 번만 실행시키는 함수
{
  Serial.begin(9600); //9600bps로 아두이노가 통신을 시작하겠다
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  distance = 0.01723 * readUltrasonicDistance(7, 6); 거리함수는 
  Serial.println(distance);
  if (distance >= 200) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  if (distance >= 100 && distance < 200) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
  if (distance < 100) {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}

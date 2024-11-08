// 핀 설정
const int ultrasonicTriggerPin = 7; // 초음파 센서 트리거 핀
const int ultrasonicEchoPin = 6;    // 초음파 센서 에코 핀
const int irSensorPin = A0;         // 적외선 센서 핀
const int motorLeftPin1 = 9;        // 왼쪽 모터 핀1
const int motorLeftPin2 = 8;        // 왼쪽 모터 핀2
const int motorRightPin1 = 11;      // 오른쪽 모터 핀1
const int motorRightPin2 = 10;      // 오른쪽 모터 핀2

// 초음파 센서의 탐지 거리 설정
const int minDistance = 5;         // 최소 탐지 거리 (cm)
const int maxDistance = 200;       // 최대 탐지 거리 (cm)

// 적외선 센서 탐지 거리 기준
const int irThreshold = 15;        // 적외선 센서 기준 거리 (cm)

// 함수 정의
void setup() {
pinMode(ultrasonicTriggerPin, OUTPUT);
pinMode(ultrasonicEchoPin, INPUT);
pinMode(irSensorPin, INPUT);
pinMode(motorLeftPin1, OUTPUT);
pinMode(motorLeftPin2, OUTPUT);
pinMode(motorRightPin1, OUTPUT);
pinMode(motorRightPin2, OUTPUT);
Serial.begin(9600); // 디버깅용 시리얼 통신
}

long getUltrasonicDistance() {
digitalWrite(ultrasonicTriggerPin, LOW);
delayMicroseconds(2);
digitalWrite(ultrasonicTriggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(ultrasonicTriggerPin, LOW);

long duration = pulseIn(ultrasonicEchoPin, HIGH);
long distance = duration * 0.034 / 2; // 시간 기반 거리 계산 (cm)
return distance;
}

void moveForward() {
digitalWrite(motorLeftPin1, HIGH);
digitalWrite(motorLeftPin2, LOW);
digitalWrite(motorRightPin1, HIGH);
digitalWrite(motorRightPin2, LOW);
}

void stopMotors() {
digitalWrite(motorLeftPin1, LOW);
digitalWrite(motorLeftPin2, LOW);
digitalWrite(motorRightPin1, LOW);
digitalWrite(motorRightPin2, LOW);
}

void rotateCounterClockwise() {
digitalWrite(motorLeftPin1, LOW);
digitalWrite(motorLeftPin2, HIGH);
digitalWrite(motorRightPin1, HIGH);
digitalWrite(motorRightPin2, LOW);
delay(500); // 120도 회전 (필요시 조정)
stopMotors();
}

void loop() {
long distance = getUltrasonicDistance();
int irValue = analogRead(irSensorPin);

if (irValue < irThreshold) {
stopMotors();
delay(30); // 정지 후 회전 준비
rotateCounterClockwise(); // 반시계 방향 회전
} else if (distance > minDistance && distance <= maxDistance) {
moveForward(); // 상대 로봇이 탐지되면 직진
} else {
stopMotors(); // 안전을 위해 기본 정지 상태 유지
}
}
// �� ����
const int ultrasonicTriggerPin = 7; // ������ ���� Ʈ���� ��
const int ultrasonicEchoPin = 6;    // ������ ���� ���� ��
const int irSensorPin = A0;         // ���ܼ� ���� ��
const int motorLeftPin1 = 9;        // ���� ���� ��1
const int motorLeftPin2 = 8;        // ���� ���� ��2
const int motorRightPin1 = 11;      // ������ ���� ��1
const int motorRightPin2 = 10;      // ������ ���� ��2

// ������ ������ Ž�� �Ÿ� ����
const int minDistance = 5;         // �ּ� Ž�� �Ÿ� (cm)
const int maxDistance = 200;       // �ִ� Ž�� �Ÿ� (cm)

// ���ܼ� ���� Ž�� �Ÿ� ����
const int irThreshold = 15;        // ���ܼ� ���� ���� �Ÿ� (cm)

// �Լ� ����
void setup() {
pinMode(ultrasonicTriggerPin, OUTPUT);
pinMode(ultrasonicEchoPin, INPUT);
pinMode(irSensorPin, INPUT);
pinMode(motorLeftPin1, OUTPUT);
pinMode(motorLeftPin2, OUTPUT);
pinMode(motorRightPin1, OUTPUT);
pinMode(motorRightPin2, OUTPUT);
Serial.begin(9600); // ������ �ø��� ���
}

long getUltrasonicDistance() {
digitalWrite(ultrasonicTriggerPin, LOW);
delayMicroseconds(2);
digitalWrite(ultrasonicTriggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(ultrasonicTriggerPin, LOW);

long duration = pulseIn(ultrasonicEchoPin, HIGH);
long distance = duration * 0.034 / 2; // �ð� ��� �Ÿ� ��� (cm)
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
delay(500); // 120�� ȸ�� (�ʿ�� ����)
stopMotors();
}

void loop() {
long distance = getUltrasonicDistance();
int irValue = analogRead(irSensorPin);

if (irValue < irThreshold) {
stopMotors();
delay(30); // ���� �� ȸ�� �غ�
rotateCounterClockwise(); // �ݽð� ���� ȸ��
} else if (distance > minDistance && distance <= maxDistance) {
moveForward(); // ��� �κ��� Ž���Ǹ� ����
} else {
stopMotors(); // ������ ���� �⺻ ���� ���� ����
}
}
const int TRIG_PIN1 = 2;  // ������ ���� Ʈ���� �� 1
const int ECHO_PIN1 = 4;  // ������ ���� ���� �� 1
const int TRIG_PIN2 = 7;  // ������ ���� Ʈ���� �� 2
const int ECHO_PIN2 = 8;  // ������ ���� ���� �� 2

const int IRSENSOR_PIN = A0; // ���ܼ� ���� ��
const int threshold = 500; // ��� �� ���� �Ӱ谪 (���� �� ȯ�濡 ���� ���� �ʿ�)

float measureDistance1() {
  digitalWrite(TRIG_PIN1, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  long duration = pulseIn(ECHO_PIN1, HIGH);

  float distance = duration * 0.033909 / 2;

  return distance; // distance1 -> distance
}

float measureDistance2() {
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW); 

  long duration = pulseIn(ECHO_PIN2, HIGH); 

  float distance = duration * 0.033909 / 2;

  return distance; // distance2 -> distance
}

void setup() {
  Serial.begin(9600);          // �ø��� ��� �ʱ�ȭ �߰�
  pinMode(TRIG_PIN1, OUTPUT);    // Ʈ���� ��1 ��� ��� ����
  pinMode(ECHO_PIN1, INPUT);     // ���� ��1 �Է� ��� ����
  pinMode(TRIG_PIN2, OUTPUT);    // Ʈ���� ��2 ��� ��� ����
  pinMode(ECHO_PIN2, INPUT);     // ���� ��2 �Է� ��� ����
  pinMode(IRSENSOR_PIN, INPUT); // ���ܼ� ���� ���� �Է� ���� ����
}


void loop() {
  float distance1 = measureDistance1(); // ���� 1 �Ÿ� ����
  float distance2 = measureDistance2();

// Serial.print("Distance 1: ");
// Serial.print(distance1);
// Serial.print(" cm, Distance 2: "); // �� �ٿ� ����ϱ� ���� println ��� print ���
// Serial.print(distance2);
// Serial.println(" cm"); // �� �ٲ�
delay(100); // ���� ���� �߰�

int sensorValue = analogRead(IRSENSOR_PIN); // ���ܼ� ���� �� �б�
Serial.println(sensorValue);
}
// if (sensorValue > threshold) {
//     // ��� �� ����!
//     Serial.println("��� �� ����!");
//     // ��� �� ���� �� ������ ���� (��: �κ� ȸ��)
//   } else {
//     // ������ �ٴ� ����!
//     Serial.println("������ �ٴ� ����!");
//     // ������ �ٴ� ���� �� ������ ���� (��: �κ� ����)
//   }
//   delay(100); // ���� ���� �д� ���� (���� ����)
// }
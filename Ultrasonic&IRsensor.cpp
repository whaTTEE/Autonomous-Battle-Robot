const int TRIG_PIN1 = 2;  // 초음파 센서 트리거 핀 1
const int ECHO_PIN1 = 4;  // 초음파 센서 에코 핀 1
const int TRIG_PIN2 = 7;  // 초음파 센서 트리거 핀 2
const int ECHO_PIN2 = 8;  // 초음파 센서 에코 핀 2

const int IRSENSOR_PIN = A0; // 적외선 센서 핀
const int threshold = 500; // 흰색 선 감지 임계값 (센서 및 환경에 따라 조정 필요)

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
  Serial.begin(9600);          // 시리얼 통신 초기화 추가
  pinMode(TRIG_PIN1, OUTPUT);    // 트리거 핀1 출력 모드 설정
  pinMode(ECHO_PIN1, INPUT);     // 에코 핀1 입력 모드 설정
  pinMode(TRIG_PIN2, OUTPUT);    // 트리거 핀2 출력 모드 설정
  pinMode(ECHO_PIN2, INPUT);     // 에코 핀2 입력 모드 설정
  pinMode(IRSENSOR_PIN, INPUT); // 적외선 센서 핀을 입력 모드로 설정
}


void loop() {
  float distance1 = measureDistance1(); // 센서 1 거리 측정
  float distance2 = measureDistance2();

Serial.print("Distance 1: ");
Serial.print(distance1);
Serial.print(" cm, Distance 2: "); // 한 줄에 출력하기 위해 println 대신 print 사용
Serial.print(distance2);
Serial.println(" cm"); // 줄 바꿈
delay(100); // 측정 간격 추가

int sensorValue = analogRead(IRSENSOR_PIN); // 적외선 센서 값 읽기
Serial.println(sensorValue);
}
if (sensorValue > threshold) {
    // 흰색 선 감지!
    Serial.println("흰색 선 감지!");
    // 흰색 선 감지 시 수행할 동작 (예: 로봇 회전)
  } else {
    // 검은색 바닥 감지!
    Serial.println("검은색 바닥 감지!");
    // 검은색 바닥 감지 시 수행할 동작 (예: 로봇 직진)
  }
  delay(100); // 센서 값을 읽는 간격 (조정 가능)
}
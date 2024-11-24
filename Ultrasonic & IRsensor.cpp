/*
 * Speed Control Test for 2 DC Motors
 * 
 * This code tests speed control by gradually increasing and decreasing the speed of both motors.
 * 
 */

const int D0 = 9; // PWM pin for Motor 1
const int D1 = 6; // PWM pin for Motor 1
const int D2 = 5; // PWM pin for Motor 2
const int D3 = 3; // PWM pin for Motor 2

bool CW = true;
bool CCW = false;

bool debug = true; // Enable debug to see speed changes

void setup() {
  Serial.begin(9600);
  Serial.println("Robojax TA6586 Motor Control - Speed Control Test");
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop() {
  // Gradually increase speed from 0 to 100% in CW direction
  for (int speed = 0; speed <= 100; speed += 10) {
    M1(CW, speed);
    M2(CW, speed);
    delay(500); // Wait 0.5 seconds at each speed level
  }

  // Apply brake to both motors
  brake(1);
  brake(2);
  delay(1000); // Wait for 1 second

  // Gradually decrease speed from 100% to 0 in CCW direction
  for (int speed = 100; speed >= 0; speed -= 10) {
    M1(CCW, speed);
    M2(CCW, speed);
    delay(500); // Wait 0.5 seconds at each speed level
  }

  // Apply brake to both motors
  brake(1);
  brake(2);
  delay(3000); // Wait for 3 seconds
}

/*
 *  M1(bool direction, int speed)
 * @brief runs motor 1
 * @param direction is CW or CCW
 * @param speed is integer between 0 to 100
 */
void M1(bool direction, int speed) {
  int pwm = map(speed, 0, 100, 0, 255);
  if (direction == CW) {
    analogWrite(D0, pwm);
    analogWrite(D1, LOW);
  } else {
    analogWrite(D1, pwm);
    analogWrite(D0, LOW);
  }
  debugPrint(1, direction, speed, false);
}

/*
 *  M2(bool direction, int speed)
 * @brief runs motor 2
 * @param direction is CW or CCW
 * @param speed is integer between 0 to 100
 */
void M2(bool direction, int speed) {
  int pwm = map(speed, 0, 100, 0, 255);
  if (direction == CW) {
    analogWrite(D2, pwm);
    analogWrite(D3, LOW);
  } else {
    analogWrite(D3, pwm);
    analogWrite(D2, LOW);
  }
  debugPrint(2, direction, speed, false);
}

/*
 *  brake(int motor)
 * @brief applies brake to a motor
 * @param "motor" is integer 1 or 2
 */
void brake(int motor) {
  if (motor == 1) {
    analogWrite(D0, HIGH);
    analogWrite(D1, HIGH);
  } else {
    analogWrite(D2, HIGH);
    analogWrite(D3, HIGH);
  }
  debugPrint(motor, true, 0, true);
}

/*
 * debugPrint(int motor, bool direction, int speed, bool stop)
 * @brief prints debugging information
 * @param "motor" is integer 1 or 2
 * @param "direction" is CW or CCW
 * @param "speed" is 0 to 100
 * @param "stop" is true or false, if true, the word "stop" is printed
 */
void debugPrint(int motor, bool direction, int speed, bool stop) {
  if (debug) {
    Serial.print("Motor: ");
    Serial.print(motor);
    if (stop && motor > 0) {
      Serial.println(" Stopped");
    } else {
      if (direction) {
        Serial.print(" CW at ");
      } else {
        Serial.print(" CCW at ");
      }
      Serial.print(speed);
      Serial.println(" %");
    }
  }
}

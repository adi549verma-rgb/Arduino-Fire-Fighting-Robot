/*
  ARDUINO FIRE FIGHTING ROBOT
  ---------------------------
  Components (as per project report):
    - 3x IR Flame sensors (Left, Center, Right)
    - L293D Motor Driver -> 2x DC Motors (differential drive)
    - Servo motor -> water nozzle aiming
    - DC water pump (switched via transistor/relay on PUMP_PIN)
    - HC-SR04 Ultrasonic sensor -> obstacle detection

  Behavior:
    - Continuously scans 3 flame sensors.
    - Turns/moves toward the direction with fire.
    - Stops and sprays water once close enough to the flame.
    - Avoids obstacles using the ultrasonic sensor while searching.
*/

#include <Servo.h>

// ===== FLAME SENSORS (digital: LOW/0 = fire detected, adjust if using analog) =====
#define FLAME_LEFT   8
#define FLAME_CENTER 9
#define FLAME_RIGHT  10

// ===== L293D MOTOR DRIVER PINS =====
#define ENA 5   // Left motor speed (PWM)
#define IN1 6
#define IN2 7
#define ENB 11  // Right motor speed (PWM)
#define IN3 12
#define IN4 13

#define MOTOR_SPEED 150   // 0-255

// ===== SERVO (water nozzle) =====
#define SERVO_PIN 3
Servo nozzleServo;

// ===== WATER PUMP =====
#define PUMP_PIN 4

// ===== ULTRASONIC SENSOR (obstacle detection) =====
#define TRIG_PIN A0
#define ECHO_PIN A1
#define OBSTACLE_DISTANCE 15   // cm

// ===== FIRE SUPPRESSION SETTINGS =====
#define FIRE_RANGE_CM   40     // start spraying once this close
#define SPRAY_DURATION  8000   // ms (5-10 sec per report)

void setup() {
  Serial.begin(9600);

  pinMode(FLAME_LEFT, INPUT);
  pinMode(FLAME_CENTER, INPUT);
  pinMode(FLAME_RIGHT, INPUT);

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  nozzleServo.attach(SERVO_PIN);
  nozzleServo.write(90); // center position

  stopMotors();
}

// ---------- Motor control ----------
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ---------- Ultrasonic ----------
int getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  if (distance <= 0 || distance > 400) distance = 400;
  return distance;
}

// ---------- Fire suppression ----------
void extinguishFire() {
  stopMotors();
  Serial.println("Fire in range - spraying water");

  // sweep nozzle while spraying for wider coverage
  digitalWrite(PUMP_PIN, HIGH);
  unsigned long start = millis();
  while (millis() - start < SPRAY_DURATION) {
    for (int pos = 60; pos <= 120; pos += 5) {
      nozzleServo.write(pos);
      delay(40);
    }
    for (int pos = 120; pos >= 60; pos -= 5) {
      nozzleServo.write(pos);
      delay(40);
    }
  }
  digitalWrite(PUMP_PIN, LOW);
  nozzleServo.write(90);
  Serial.println("Fire extinguished, resuming patrol");
}

void loop() {
  bool leftFire   = (digitalRead(FLAME_LEFT)   == LOW);
  bool centerFire = (digitalRead(FLAME_CENTER) == LOW);
  bool rightFire  = (digitalRead(FLAME_RIGHT)  == LOW);

  if (!leftFire && !centerFire && !rightFire) {
    // No fire detected -> patrol forward, avoid obstacles
    int distance = getDistanceCM();
    if (distance < OBSTACLE_DISTANCE) {
      stopMotors();
      turnRight();
      delay(400);
    } else {
      moveForward();
    }
    return;
  }

  // Fire detected: steer toward it
  if (centerFire) {
    int distance = getDistanceCM();
    if (distance <= FIRE_RANGE_CM) {
      extinguishFire();
    } else {
      moveForward();
    }
  } else if (leftFire) {
    turnLeft();
    delay(200);
  } else if (rightFire) {
    turnRight();
    delay(200);
  }

  delay(100);
}

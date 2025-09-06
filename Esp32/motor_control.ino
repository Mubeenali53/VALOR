/*
* File: esp32_motor_control.ino
* Description: Receives motion/speed commands from Jetson Nano via Serial
* and controls 4 DC motors via BTS7960 drivers using PWM.
*/

#define PWM_FREQ 1000
#define PWM_RES 8

// ===== Motor Pins =====
// Motor 1 (Front Left)
#define M1_EN 14
#define M1_IN1 27
#define M1_IN2 26

// Motor 2 (Front Right)
#define M2_EN 25
#define M2_IN1 33
#define M2_IN2 32

// Motor 3 (Rear Left)
#define M3_EN 23
#define M3_IN1 19
#define M3_IN2 18

// Motor 4 (Rear Right)
#define M4_EN 5
#define M4_IN1 17
#define M4_IN2 16

String command = "";

// ===== Setup =====
void setup() {
  Serial.begin(115200);

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);
  pinMode(M4_IN1, OUTPUT);
  pinMode(M4_IN2, OUTPUT);

  // Setup PWM channels
  ledcAttachPin(M1_EN, 0);
  ledcAttachPin(M2_EN, 1);
  ledcAttachPin(M3_EN, 2);
  ledcAttachPin(M4_EN, 3);

  ledcSetup(0, PWM_FREQ, PWM_RES);
  ledcSetup(1, PWM_FREQ, PWM_RES);
  ledcSetup(2, PWM_FREQ, PWM_RES);
  ledcSetup(3, PWM_FREQ, PWM_RES);

  stopAllMotors();
}

// ===== Loop =====
void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "FORWARD") {
      moveAllMotors(200, true);
    } else if (command == "SLOW") {
      moveAllMotors(100, true);
    } else if (command == "BACKWARD") {
      moveAllMotors(200, false);
    } else if (command == "LEFT") {
      turnLeft(150);
    } else if (command == "RIGHT") {
      turnRight(150);
    } else if (command == "STOP") {
      stopAllMotors();
    }

    Serial.println("Received: " + command);
  }
}

// ===== Functions =====

// Move all motors forward or backward
void moveAllMotors(int speed, bool forward) {
  motorControl(M1_IN1, M1_IN2, 0, speed, forward);
  motorControl(M2_IN1, M2_IN2, 1, speed, forward);
  motorControl(M3_IN1, M3_IN2, 2, speed, forward);
  motorControl(M4_IN1, M4_IN2, 3, speed, forward);
}

// Stop all motors
void stopAllMotors() {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);

  digitalWrite(M1_IN1, LOW); digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW); digitalWrite(M2_IN2, LOW);
  digitalWrite(M3_IN1, LOW); digitalWrite(M3_IN2, LOW);
  digitalWrite(M4_IN1, LOW); digitalWrite(M4_IN2, LOW);
}

// Turn left (right motors forward, left motors backward)
void turnLeft(int speed) {
  motorControl(M1_IN1, M1_IN2, 0, speed, false);  // Left motors backward
  motorControl(M3_IN1, M3_IN2, 2, speed, false);
  motorControl(M2_IN1, M2_IN2, 1, speed, true);   // Right motors forward
  motorControl(M4_IN1, M4_IN2, 3, speed, true);
}

// Turn right (left motors forward, right motors backward)
void turnRight(int speed) {
  motorControl(M1_IN1, M1_IN2, 0, speed, true);   // Left motors forward
  motorControl(M3_IN1, M3_IN2, 2, speed, true);
  motorControl(M2_IN1, M2_IN2, 1, speed, false);  // Right motors backward
  motorControl(M4_IN1, M4_IN2, 3, speed, false);
}

// Generic motor control
void motorControl(int in1, int in2, int channel, int speed, bool forward) {
  if (forward) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  ledcWrite(channel, speed);
}

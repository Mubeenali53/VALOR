/*
* File: esp32_motor_control.ino
* Description: Receives speed commands ("FORWARD", "SLOW", "STOP")
* from Jetson Nano via Serial and controls DC motors via PWM.
*/
#define ENA 14 // PWM pin
#define IN1 27
#define IN2 26

String command = "";
void setup() {
Serial.begin(115200);
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
stopMotor();
}

void loop() {
if (Serial.available()) {
command = Serial.readStringUntil('\n');
command.trim();
if (command == "FORWARD") {
forwardMotor(200); // Full speed
} else if (command == "SLOW") {
forwardMotor(100); // Slow speed
} else if (command == "STOP") {
stopMotor();
}
Serial.println("Received: " + command);
}
}
void forwardMotor(int speed) {
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
analogWrite(ENA, speed);
}
void stopMotor() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
analogWrite(ENA, 0);
}
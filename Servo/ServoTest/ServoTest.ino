#include <Servo.h>

Servo myServo;

int servo_pin = 6;
int led_pin = 13;
int angle = 0;
bool changed = false;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(servo_pin, OUTPUT);
  myServo.attach(servo_pin);
  myServo.write(angle);
  Serial.begin(115200);
}

void loop() {
  if (!changed) {
    angle++;
    digitalWrite(led_pin, HIGH);
  } else {
    angle--;
    digitalWrite(led_pin, LOW);
  }

  if (angle >= 180) changed = true;
  if (angle <= 0) changed = false;

  Serial.println(angle);
  myServo.write(angle);

  delay(50);
}

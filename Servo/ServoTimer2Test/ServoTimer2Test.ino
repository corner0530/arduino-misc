#include <ServoTimer2.h>

ServoTimer2 servo1;

int val = 1000;
int mode = 0;

//MAX2200
//MIN

#define SERVO_PIN 5
#define DELAY_TIME 50

void setup() {
  servo1.attach(SERVO_PIN);
  Serial.begin(115200);
}

void loop() {
  if (mode) {
    val += 5;
    servo1.write(val);  // min pulse width for 0 degree
  } else {
    val -= 5;
    servo1.write(val);
  }
  Serial.println(val);
  if (val <= 950)
    mode++;
  else if (val >= 1000)
    mode--;
  delay(DELAY_TIME);
}

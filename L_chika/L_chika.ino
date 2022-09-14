#include <MsTimer2.h>
#define VAL 500
int pin = 12;

void flash();

void setup() {
  pinMode(pin, OUTPUT);
  MsTimer2::set(VAL, flash);
  MsTimer2::start();
}

void loop() {
}

void flash() {
  static boolean output = HIGH;
  digitalWrite(pin, output);
  output = !output;
}

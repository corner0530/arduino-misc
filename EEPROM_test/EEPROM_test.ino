#include <EEPROM.h>

void setup() {
  // EEPROM.write(0, 90);
  Serial.begin(38400);
}

void loop() {
  int val = (int)(EEPROM.read(0)) - 90;
  Serial.println(val);
  delay(1000);
}

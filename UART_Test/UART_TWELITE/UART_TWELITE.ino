#include <SoftwareSerial.h>
SoftwareSerial TWE(5,6); // RX, TX

#define LED 13

void setup() {
  TWE.begin(38400);
  Serial.begin(38400);
  pinMode(LED, OUTPUT);
}

void loop() {
  char recv = 0;
  while (TWE.available()) {
    digitalWrite(LED, HIGH);
    recv = TWE.read();
    Serial.print(recv);
  }
  digitalWrite(LED, LOW);
}

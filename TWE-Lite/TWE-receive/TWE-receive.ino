#include <SoftwareSerial.h>
SoftwareSerial TWE(2,3); // RX, TX
#define LED 9

void setup() {
  TWE.begin(38400);
  Serial.begin(38400);
  pinMode(LED, OUTPUT);
}

void loop() {
  char recv[60] = {};
  byte count = 0;

  //receive data
  while (TWE.available()) {
    digitalWrite(LED, HIGH);
    recv[count] = TWE.read();
    count++;
  }
  for (byte i = 0; i < count; i++) Serial.print(recv[i]);
  digitalWrite(LED, LOW);
}

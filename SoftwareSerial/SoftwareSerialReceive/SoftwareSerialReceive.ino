#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(57600); // シリアルモニタ用
  Serial.println("Ready");
  mySerial.begin(4800);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

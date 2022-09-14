#include <SoftwareSerial.h>

// rxPin = 11  txPin = 10
SoftwareSerial mySerial(11, 10);

void setup() {
  mySerial.begin(9600);
  Serial.begin(115200);
}
void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

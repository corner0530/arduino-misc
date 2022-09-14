#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

char key;
String buffer;

void setup() {
  Serial.begin(9600);
  Serial.println("ready");
  mySerial.begin(115200);
}

void loop() {
  //mySerial.println(); // Arduino1に文字（改行のみ）を送る
  //Serial.println(mySerial.read());
  if (mySerial.available()){
    buffer = mySerial.readStringUntil('\n');
    //key = mySerial.read();
    Serial.println(buffer);
  }
  delay(1000);
}

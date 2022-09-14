/*#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6); // RX, TX*/

int val = 0;

void setup() {
  //mySerial.begin(115200);
  Serial.begin(115200);
}

void loop() {
  val++;
  if(val > 99) val = 0;

  char output[2] = {'\0'};
  sprintf(output, "%02d", val);

  Serial.println(output);
  delay(1000);
}

int val = 0;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    String buffer = Serial.readStringUntil('\n');
    val = buffer.toInt();
    //Serial.println(buffer);
  }
  if (val % 2 == 0) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  delay(1000);
}

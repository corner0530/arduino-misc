int val = 0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  val = 1 - val;
  Serial.write(val);
  delay(500);
}

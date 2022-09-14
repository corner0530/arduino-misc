int val = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  pinMode(49, INPUT_PULLUP);
}

void loop() {
  val = digitalRead(49);
  Serial.println(val);
  delay(500);
}

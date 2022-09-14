#define SP_PIN 48
void setup() {
  pinMode(SP_PIN, OUTPUT);
}

void loop() {
  //pin++;
  //Serial.println(pin);
  tone(SP_PIN, 1000, 1000);
  delay(2000);
}

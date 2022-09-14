#define LED_PIN 13

int val;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    val = Serial.read();
    if (val) digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);
  }
}

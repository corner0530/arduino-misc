unsigned long pw_alt, adc_alt;

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT);
  pinMode(7, INPUT);
}

void loop() {
  pw_alt = pulseIn(7, HIGH) / 58;
  adc_alt = analogRead(0) * 21 / 10;
  Serial.print(pw_alt);
  Serial.print(", ");
  Serial.print(adc_alt);
  Serial.println();
  delay(100);
}

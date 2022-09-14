#define AIR_SPEED_SENSOR 9
#define LED 3

int AirSpeed = 0;
unsigned long temp = 0;

void setup() {
  pinMode(AIR_SPEED_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  temp = pulseIn(AIR_SPEED_SENSOR, HIGH);
  Serial.println(temp);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
}

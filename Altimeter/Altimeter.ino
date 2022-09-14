const int in_num = 14;
const int out_num = 5;

void setup() {
    Serial.begin(9600);
    Serial.println("ready");
    pinMode(in_num, INPUT);
}

void loop() {
  int val = analogRead(in_num);
  //analogWrite(out_num,val/4);
  Serial.println(val);
  delay(100);
}

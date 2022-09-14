#include <SoftwareSerial.h>
SoftwareSerial TWE(5, 6); // RX, TX

#define LED 13
#define DATA_SIZE 4

int val = 0;

void setup() {
  TWE.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH); // 確認用LED
  byte DATA_START[5] = {':', '7', '8', '0', '1'};
  for (byte i = 0; i < 5; i++) TWE.write(DATA_START[i]);
  
  char DATA[DATA_SIZE] = {'0', '0', '0', '0'};
  for (byte i = 0; i < DATA_SIZE; i++) TWE.write(DATA[i]);
  /*String DATA = "0000";
  for (byte i = 0; i <TWE.write(DATA);*/
  
  byte DATA_END[3] = {'X', '\r', '\n'};
  for (byte i = 0; i < 3; i++) TWE.write(DATA_END[i]);

  digitalWrite(LED, LOW); // 確認用LED
  delay(500);

}

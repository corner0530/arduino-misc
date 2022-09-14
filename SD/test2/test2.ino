#include <SD.h>
#include <SPI.h>

File myFile;

void setup() {
  pinMode(53, OUTPUT);  // SD
  pinMode(A2, OUTPUT);  // BME
  digitalWrite(53, LOW);
  digitalWrite(A2, HIGH);
  Serial.begin(9600);
  Serial.print("Start");

  if (!SD.begin(53)) {
    Serial.println("initialization error");
  }
}

void loop() {
  myFile = SD.open("test2.txt", FILE_WRITE);
  int time = millis();
  if (myFile) {
    myFile.println(time);
    myFile.close();
    Serial.println("Success.");
  } else {
    Serial.println("opening error");
  }
  delay(500);
}

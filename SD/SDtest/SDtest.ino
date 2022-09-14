#include <SD.h>
#include <SPI.h>

File myFile;

void setup() {
  pinMode(53, OUTPUT);  // SD
  digitalWrite(53, HIGH);
  pinMode(A2, OUTPUT);  // BME
  digitalWrite(A2, HIGH);
  digitalWrite(53, LOW);
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");

    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");
  }

  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

void loop() {
}

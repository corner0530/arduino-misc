#include <SPI.h>
#include <ServoTimer2.h>

#define SERVO_PIN 2
#define INTERVAL 100

ServoTimer2 myServo;
volatile byte receiveValue;
int angle = 90;

void setup(){
    SPCR |= bit(SPE); // SPI制御レジスタを操作
    pinMode(MISO,OUTPUT); // Master In Slave Out
    SPI.attachInterrupt();  // 割り込みサービスルーチン(ISR)の定義

    Serial.begin(115200);
    Serial.println("Ready");

    myServo.attach(SERVO_PIN);
}


void loop(){
  //analogWrite(9,receiveValue);
  angle = (receiveValue - 128) * 15 / 2 + 1500;
  Serial.print("joyx: "); Serial.print((byte)receiveValue, DEC);
  Serial.print(" angle: "); Serial.println(angle, DEC);
  myServo.write(angle);
  delay(INTERVAL);
}

ISR(SPI_STC_vect){  // ISRの内容
    receiveValue = SPDR;  // SPDRは送信・受信するデータが入っている
}

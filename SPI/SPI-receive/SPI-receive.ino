#include <SPI.h>
  
volatile byte receiveValue;

int val1 = 0, val2 = 0;
int val1_u = 0, val1_l = 0, val2_u = 0, val2_l = 0;
bool renew1u = false, renew1l = false, renew2u = false, renew2l = false;
  
void setup(){
    SPCR |= bit(SPE); // SPI制御レジスタを操作
    pinMode(MISO,OUTPUT); // Master In Slave Out
    SPI.attachInterrupt();  // 割り込みサービスルーチン(ISR)の定義

    Serial.begin(115200);
}

void loop(){
  /*if (receiveValue < B01000000) {
    // B00000000~B00111111
    val1_l = receiveValue;
  }
  else if (receiveValue < B10000000) {
    // B01000000~B01111111
    val1_u = receiveValue;
    val1_u &= B10111111;
  }
  else if (receiveValue < B11000000) {
    // B10000000~B10111111
    val2_l = receiveValue;
    val2_l &= B01111111;
  }
  else {
    // B11000000~B11111111
    val2_u = receiveValue;
    val2_u &= B00111111;
  }
  val1 = (val1_u << 6) + val1_l;
  val2 = (val2_u << 6) + val2_l;
  Serial.print(val1); Serial.print(",");Serial.println(val2);*/
  Serial.print(val1); Serial.print(","); Serial.println(val2);
  delay(200);
}

ISR(SPI_STC_vect){  // ISRの内容
    receiveValue = SPDR;  // SPDRは送信・受信するデータが入っている
    if (receiveValue < B01000000) {
    // B00000000~B00111111
    val1_l = receiveValue;
    renew1l = true;
  }
  else if (receiveValue < B10000000) {
    // B01000000~B01111111
    val1_u = receiveValue;
    val1_u &= B10111111;
    if(renew1l) renew1u = true;
  }
  else if (receiveValue < B11000000) {
    // B10000000~B10111111
    val2_l = receiveValue;
    val2_l &= B01111111;
    renew2l = true;
  }
  else {
    // B11000000~B11111111
    val2_u = receiveValue;
    val2_u &= B00111111;
    if(renew2l) renew2u = true;
  }
  if (renew1l && renew1u) {
    val1 = (val1_u << 6) + val1_l;
    renew1l = false;
    renew1u = false;
  }
  if (renew2l && renew2u) {
    val2 = (val2_u << 6) + val2_l;
    renew2l = false;
    renew2u = false;
   }
  //Serial.print(val1); Serial.print(","); Serial.println(val2);
}

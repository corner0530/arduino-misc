#include <SPI.h>

int val1 = 0, val2 = 0;
uint8_t val1_l, val1_u, val2_l, val2_u;

void SPIsend(uint8_t val){
  digitalWrite(SS, LOW);
  SPI.transfer(val);
  digitalWrite(SS, HIGH);
  delay(10);
}

void setup(){ 
  SPI.begin();
  digitalWrite(SS, HIGH);
}

void loop(){
  val1 += 2;
  val2 += 3;
  
  val1_l = ((uint8_t)val1) & B00111111; // B00000000~B00111111
  val1_u = (((uint8_t)(val1 >> 6)) & B00111111) | B01000000; // B01000000~B01111111


  val2_l = (((uint8_t)val2) & B00111111) | B10000000; // B10000000~B10111111
  val2_u = (((uint8_t)(val2 >> 6)) & B00111111) | B11000000; // B11000000~B11111111

  SPIsend(val1_l);
  SPIsend(val1_u);
  SPIsend(val2_l);
  SPIsend(val2_u);
  delay(100);
}

#include <Wire.h>
#include <SPI.h>
#include "nunchuck_funcs.h"

#define INTERVAL 200

int loop_cnt = 0;
byte accx,accy,accz,joyx,joyy,zbut,cbut; // ヌンチャクの値を格納

void setup() {
  // ヌンチャク初期化
  nunchuck_setpowerpins();
  nunchuck_init();
  // SPI初期化
  SPI.begin();
  digitalWrite(SS, HIGH);
}

void loop() {
  if( loop_cnt > INTERVAL ) { // 200msおきに更新
    loop_cnt = 0;

    nunchuck_get_data();

    //accx  = nunchuck_accelx();
    //accy  = nunchuck_accely();
    //accz  = nunchuck_accelz();
    joyx  = nunchuck_joyx(); // 28-129-224
    //joyy  = nunchuck_joyy();    
    //zbut = nunchuck_zbutton();
    //cbut = nunchuck_cbutton(); 

    digitalWrite(SS, LOW);
    SPI.transfer(joyx);
    digitalWrite(SS, HIGH);
  }
  loop_cnt++;
  delay(1);
}

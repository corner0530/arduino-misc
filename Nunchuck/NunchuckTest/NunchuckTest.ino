#include <Wire.h>
#include "nunchuck_funcs.h"

// ジョイコン(縦・横)の最大値・初期値・最小値
#define ELEVATOR_CENTER 136
#define ELEVATOR_MIN 37
#define ELEVATOR_MAX 230
#define RUDDER_CENTER 129
#define RUDDER_MIN 28
#define RUDDER_MAX 226

int loop_cnt=0;
byte accx,accy,accz,joyx,joyy,zbut,cbut;
int x = 90, y = 90, z = 0, c = 0;

void setup()
{
    Serial.begin(115200);
    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake
    Serial.println("WiiChuckDemo ready");
}

void loop() {
  if( loop_cnt > 100 ) { // every 100 msecs get new data
    loop_cnt = 0;

    nunchuck_get_data();

    joyx  = nunchuck_joyx();
    joyy  = nunchuck_joyy();
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton(); 
    
    /*if (joyx <= RUDDER_CENTER) {
      // 左側に倒したとき
      // マイナスにならないようにする
      x = max(0, 90 - (int)(((float)(RUDDER_CENTER - joyx) / (float)(RUDDER_CENTER - RUDDER_MIN)) * 90.0));
    } else {
      // 右側に倒したとき
      // 180は超えないようにする
      x = min(180, 90 + (int)(((float)(joyx - RUDDER_CENTER) / (float)(RUDDER_MAX - RUDDER_CENTER)) * 90.0));
    }
    if (joyy <= ELEVATOR_CENTER) {
      // 下側に倒したとき
      // マイナスにならないようにする
      y = max(0, 90 - (int)(((float)(ELEVATOR_CENTER - joyy) / (float)(ELEVATOR_CENTER - ELEVATOR_MIN)) * 90.0));
    } else {
      // 上側に倒したとき
      // 180は超えないようにする
      y = min(180, 90 + (int)(((float)(joyy - ELEVATOR_CENTER) / (float)(ELEVATOR_MAX - ELEVATOR_CENTER)) * 90.0));
    }
    Serial.print("x: "); Serial.print(x, DEC);
    Serial.print(" y: "); Serial.print(y, DEC);
    Serial.print(" zbut: "); Serial.print(zbut, DEC);
    Serial.print(" cbut: "); Serial.println(cbut, DEC);*/
  }
  loop_cnt++;
  delay(1);
}

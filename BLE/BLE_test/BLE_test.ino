#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

//  高度・回転数・気速
uint16_t altitude=0, rotation=0, airspeed=0;
//  ヨー・ピッチ・ロール・トリム量・ラダー操作量・エレベータ操作量
int16_t yaw=0, pitch=0, roll=0, servo_trim=0, servo_rudder=90, servo_elev=90;
// 格納用(1バイトずつ送るので分割する用)
uint8_t altitude_U, altitude_L, rotation_U, rotation_L, airspeed_U, airspeed_L;
uint8_t pitch_U, pitch_L, roll_U, roll_L, trim_L, rud_L, elev_L;
//  符号？+画面切り替え
uint8_t pitch_sign = 0x00, roll_sign = 0xff, trim_sign = 0x00, screen_toggle = 0x00;

void processData() {
  altitude_U = (uint8_t) (altitude >> 8); altitude_L = (uint8_t) (altitude);
  rotation_U = (uint8_t) (rotation >> 8); rotation_L = (uint8_t) (rotation); 
  airspeed_U = (uint8_t) (airspeed >> 8); airspeed_L = (uint8_t) (airspeed); 
  pitch_U = (uint8_t) (pitch >> 8); pitch_L = (uint8_t) (pitch); 
  roll_U = (uint8_t) (roll >> 8); roll_L = (uint8_t) (roll); 
  trim_L = (uint8_t) (servo_trim);
  rud_L = (uint8_t) (servo_rudder);
  elev_L = (uint8_t) (servo_elev);
}

void genRandomData(){
    altitude = random(0, 1070);   // [x1] 0cm to 1070cm
    rotation = random(0, 5000);   // [x0.1] 0rpm to 500rpm
    airspeed = random(0, 10000);  // [x0.001] 0m/s to 10m/s
    pitch = random(-1800, 1800);    // [x0.1] -180deg to 180deg
    roll = random(-1800, 1800);     // [x0.1] -180deg to 180deg
    servo_trim = 10;
    trim_sign = 0xff;
    
    // +: 0x00, -:0xff 
    if (pitch < 0){
      pitch_sign = 0xff;
      pitch = -pitch;
    } else {
      pitch_sign = 0x00;
    }
    if (roll < 0){
      roll_sign = 0xff;
      roll = -roll;
    } else {
      roll_sign = 0x00;
    }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
}

void loop() {
  genRandomData();
  processData();
  uint8_t sensorDataArr[17] = {altitude_U, altitude_L, rotation_U, rotation_L, airspeed_U, airspeed_L, pitch_sign, pitch_U, pitch_L, roll_sign, roll_U, roll_L, trim_sign, trim_L, screen_toggle, elev_L, rud_L};
  //if (SerialBT.available()) {
    for (int i = 0; i < 17; i++) {
      SerialBT.print(sensorDataArr[i]);
    }
    SerialBT.println();
  //}
  for (int i = 0; i < 17; i++) {
    Serial.print(sensorDataArr[i],HEX);
  }
  Serial.println();
  delay(100);
}

#include <Wire.h>
#include <SoftwareSerial.h>
#include "nunchuck_funcs.h"

int loop_cnt=0;

byte accx,accy,accz,joyx,joyy,zbut,cbut;
int ledPin = 13;
const int loop_time = 200; // time to get new data (ms)

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
    //Serial.begin(115200);
    mySerial.begin(4800);
    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake

    //Serial.println("Ready");
    mySerial.println("Ready");
}

void loop()
{
    if( loop_cnt > loop_time ) {
        loop_cnt = 0;

        nunchuck_get_data();

        accx  = nunchuck_accelx();
        accy  = nunchuck_accely();
        accz  = nunchuck_accelz();
        joyx  = nunchuck_joyx(); // 28-129-224
        joyy  = nunchuck_joyy(); // 40-137-229
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 
        /*
        Serial.print("accx: "); Serial.print((byte)accx,DEC);
        Serial.print(" accy: "); Serial.print((byte)accy,DEC);
        Serial.print(" accz: "); Serial.print((byte)accz,DEC);
        Serial.print(" joyx: "); Serial.print((byte)joyx, DEC);
        Serial.print(" joyy: "); Serial.print((byte)joyy,DEC);
        Serial.print(" taccy: "); Serial.print((byte)accy,DEC);
        Serial.print(" tzbut: "); Serial.print((byte)zbut,DEC);
        Serial.print(" tcbut: "); Serial.println((byte)cbut,DEC);*/
        mySerial.print("joyx: "); mySerial.print((byte)joyx, DEC);
        mySerial.print(" joyy: "); mySerial.println((byte)joyy, DEC);
    }
    loop_cnt++;
    delay(1);
}

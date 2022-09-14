#include <ServoTimer2.h>
#include <Wire.h>
//#include <Servo.h>
#include "nunchuck_funcs.h"

#define SERVO_PIN 2

ServoTimer2 myServo;
//Servo myServo;

int loop_cnt = 0;

byte accx,accy,accz,joyx,joyy,zbut,cbut;

int angle = 90;

void setup()
{
    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake

    Serial.begin(115200);
    Serial.print("WiiChuckDemo ready\n");

    myServo.attach(SERVO_PIN);
}

void loop()
{
    if( loop_cnt > 200 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();

        accx  = nunchuck_accelx();
        accy  = nunchuck_accely();
        accz  = nunchuck_accelz();
        joyx  = nunchuck_joyx(); // 28-129-224
        joyy  = nunchuck_joyy();    
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 

        angle = (joyx - 128) * 15 / 2 + 1500;
        
        //Serial.print("accx: "); Serial.print((byte)accx,DEC);
        //Serial.print(" accy: "); Serial.print((byte)accy,DEC);
        //Serial.print(" accz: "); Serial.print((byte)accz,DEC);
        Serial.print("joyx: "); Serial.print((byte)joyx, DEC);
        //Serial.print(" joyy: "); Serial.print((byte)joyy,DEC);
        //Serial.print(" taccy: "); Serial.print((byte)accy,DEC);
        //Serial.print(" tzbut: "); Serial.print((byte)zbut,DEC);
        //Serial.print(" tcbut: "); Serial.println((byte)cbut,DEC);
        Serial.print(" angle: "); Serial.println(angle, DEC);

        myServo.write(angle);
    }
    loop_cnt++;
    delay(1);
}

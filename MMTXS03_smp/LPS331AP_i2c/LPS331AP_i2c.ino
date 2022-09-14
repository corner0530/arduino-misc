/*
    MM-TXS03(LPS331AP) control sample
    for I2C connecting
    2014/2/3 Sunhayato Corp.
*/

#include <Wire.h>

/*
connecting

MM-TXS03(LPS331AP)  Arduino(Duemilanove/UNO)
1:VDD---------------5V
2:GND---------------GND
3:SDA---------------A4(I2C:SDA)
4:CLK---------------A5(I2C:SCL)
5:SDO(SA0)----------GND
6:INT1
7:INT2
8:CS----------------5V

*/

// LSP331AP I2C Address
#define LPS331_ADDR0    0b1011100   // SA0=0(GND)
#define LPS331_ADDR1    0b1011101   // SA0=1(VDD)

byte Addr = LPS331_ADDR0;


// register addr
#define LPS331_WHO_AM_I       0x0F

#define LPS331_PRESS_OUT_XL   0x28
#define LPS331_PRESS_OUT_L    0x29
#define LPS331_PRESS_OUT_H    0x2A

#define LPS331_TEMP_OUT_L     0x2B
#define LPS331_TEMP_OUT_H     0x2C

#define LPS331_CTRL_REG1      0x20
#define LPS331_CTRL_REG2      0x21
#define LPS331_CTRL_REG3      0x22


void setup()
{
    byte who_am_i;
    
    Serial.begin(9600);
    
    Wire.begin();
    
    who_am_i = readReg(Addr, LPS331_WHO_AM_I);
    if (who_am_i != 0xBB){
        Serial.println("Failed to detect LPS331");
        while(1);
    }
    
    
    writeReg(Addr, LPS331_CTRL_REG1, 0b11100000); // init sensor
}

void loop()
{
    uint8_t pxl, pl, ph;
    uint8_t tl, th;
    
    int16_t temp_raw;
    int32_t pres_raw;
    
    float tempC;
    float pressure;
    
    
    pxl = readReg(Addr, LPS331_PRESS_OUT_XL);
    pl  = readReg(Addr, LPS331_PRESS_OUT_L);
    ph  = readReg(Addr, LPS331_PRESS_OUT_H);
    
    tl  = readReg(Addr, LPS331_TEMP_OUT_L);
    th  = readReg(Addr, LPS331_TEMP_OUT_H);
    
    pres_raw = (int32_t)ph << 16 | (uint16_t)pl << 8 | pxl;
    temp_raw = (int16_t)th << 8 | tl;
    
    pressure = (float)pres_raw / 4096;
    tempC    = 42.5 + (float)temp_raw / 480;
    
    Serial.print("p: ");
    Serial.print(pressure);
    Serial.print(" mbar\ta: ");
    Serial.print(tempC);
    Serial.println(" deg C");
    
    delay(500);
}


void writeReg(byte addr, byte reg, byte value)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}


byte readReg(byte addr, byte reg)
{
    byte data;
    
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(addr, (byte)1);
    data = Wire.read();
    Wire.endTransmission();
    
    return (data);
}

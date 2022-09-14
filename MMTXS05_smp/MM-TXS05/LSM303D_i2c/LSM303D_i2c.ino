/*
    MM-TXS05(LSM303D) control sample
    for I2C connecting
    2014/2/3 Sunhayato Corp.
*/

#include <Wire.h>

/*
connecting

MM-TXS05(LSM303D)   Arduino(Duemilanove/UNO)
1:VDD---------------5V
2:GND---------------GND
3:SDA---------------A4(I2C:SDA)
4:CLK---------------A5(I2C:SCL)
5:SDO(SA0)----------GND
6:INT1
7:INT2
8:CS----------------5V
*/

#include <Wire.h>


// LSM303D I2C address
#define LSM303D_ADDR0   0b0011110  // SA0=0(GND)
#define LSM303D_ADDR1   0b0011101  // SA0=1(VDD)

byte Addr = LSM303D_ADDR0;

// LSM303D I2C Register Map
#define LSM303D_TEMP_OUT_L      0x05    // r
#define LSM303D_TEMP_OUT_H      0x06    // r
#define LSM303D_STATUS_M        0x07    // r
#define LSM303D_OUT_X_L_M       0x08    // r
#define LSM303D_OUT_X_H_M       0x09    // r
#define LSM303D_OUT_Y_L_M       0x0A    // r
#define LSM303D_OUT_Y_H_M       0x0B    // r
#define LSM303D_OUT_Z_L_M       0x0C    // r
#define LSM303D_OUT_Z_H_M       0x0D    // r
#define LSM303D_WHO_AM_I        0x0F    // r
#define LSM303D_CTRL0           0x1F    // rw
#define LSM303D_CTRL1           0x20    // rw
#define LSM303D_CTRL2           0x21    // rw
#define LSM303D_CTRL3           0x22    // rw
#define LSM303D_CTRL4           0x23    // rw
#define LSM303D_CTRL5           0x24    // rw
#define LSM303D_CTRL6           0x25    // rw
#define LSM303D_CTRL7           0x26    // rw
#define LSM303D_STATUS_A        0x27    // r
#define LSM303D_OUT_X_L_A       0x28    // r
#define LSM303D_OUT_X_H_A       0x29    // r
#define LSM303D_OUT_Y_L_A       0x2A    // r
#define LSM303D_OUT_Y_H_A       0x2B    // r
#define LSM303D_OUT_Z_L_A       0x2C    // r
#define LSM303D_OUT_Z_H_A       0x2D    // r


void setup() {
    
    byte data;
    
    Serial.begin(9600);
    
    Wire.begin();
    
    readReg(Addr, LSM303D_WHO_AM_I, 1, &data);
    
    if (data != 0x49){
        Serial.println("Failed to detect LSM303D");
        while (1);
    }
    
    
    writeReg(Addr, LSM303D_CTRL0, 0x00);   // Default
    writeReg(Addr, LSM303D_CTRL1, 0x5F);   // Acc data rate = 50Hz, BDU enable
    writeReg(Addr, LSM303D_CTRL2, 0x18);   // Acc full-scale = 8g
    writeReg(Addr, LSM303D_CTRL3, 0x00);   // INT1 disable
    writeReg(Addr, LSM303D_CTRL4, 0x00);   // INT2 disable
    writeReg(Addr, LSM303D_CTRL5, 0xF0);   // Temp enable, M data rate = 50Hz
    writeReg(Addr, LSM303D_CTRL6, 0x60);   // +/-12gauss
    writeReg(Addr, LSM303D_CTRL7, 0x00);   // Continuous-conversion mode
    
}

void loop() {
    
    byte Buffer_M[7];
    byte Buffer_A[7];
    byte Buffer_TEMP[2];
    
    short AccelRaw_x, AccelRaw_y, AccelRaw_z;
    short MagnRaw_x, MagnRaw_y, MagnRaw_z;
    short TempRaw;
    
    float Accel_x, Accel_y, Accel_z;
    float Magn_x,  Magn_y,  Magn_z;
    float Temp;
    
    readReg(Addr, LSM303D_STATUS_A,    7, Buffer_A);
    readReg(Addr, LSM303D_STATUS_M,    7, Buffer_M);
    readReg(Addr, LSM303D_TEMP_OUT_L,  2, Buffer_TEMP);
    
    
    AccelRaw_x = ((Buffer_A[2] << 8) | Buffer_A[1]);
    AccelRaw_y = ((Buffer_A[4] << 8) | Buffer_A[3]);
    AccelRaw_z = ((Buffer_A[6] << 8) | Buffer_A[5]);
    
    MagnRaw_x  = ((Buffer_M[2] << 8) | Buffer_M[1]);
    MagnRaw_y  = ((Buffer_M[4] << 8) | Buffer_M[3]);
    MagnRaw_z  = ((Buffer_M[6] << 8) | Buffer_M[5]);
    
    TempRaw    = (Buffer_TEMP[1] << 8) | Buffer_TEMP[0];
    
    // convert to +/-8g 0.244mg/LSB
    Accel_x = (float)AccelRaw_x * 0.244;
    Accel_y = (float)AccelRaw_y * 0.244;
    Accel_z = (float)AccelRaw_z * 0.244;
    
    // convert to +/-12gauss 0.479mgauss/LSB
    Magn_x = (float)MagnRaw_x * 0.479;
    Magn_y = (float)MagnRaw_y * 0.479;
    Magn_z = (float)MagnRaw_z * 0.479;
    
    // Temperature (8LSB/C)
    Temp   = 25 + (float)TempRaw / 8;
    
    
    // output serial
    Serial.print("|Temp:\t");
    Serial.print(Temp);
    
    Serial.print(",\t|");
    Serial.print("Accel:\t");
    Serial.print(Accel_x);
    Serial.print(",\t");
    Serial.print(Accel_y);
    Serial.print(",\t");
    Serial.print(Accel_z);
    Serial.print(",\t|");
    
    Serial.print("Magn:\t");
    Serial.print(Magn_x);
    Serial.print(",\t");
    Serial.print(Magn_y);
    Serial.print(",\t");
    Serial.print(Magn_z);
    Serial.print("\n");
    
    
    delay(500);
}


void writeReg(byte addr, byte reg, byte value)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}


void readReg(byte addr, byte reg, byte len, byte *data)
{
    byte i;
    
    Wire.beginTransmission(addr);
    Wire.write(reg | 0x80);         // bit7-ON (subaddress updating)
    Wire.endTransmission();
    
    Wire.requestFrom(addr, len);
    
    for (i = 0; i < len; i++){
        if (Wire.available()){
            *data = Wire.read();
        } else {
            *data = 0x00;
        }
        data ++;
    }
    
    Wire.endTransmission();
}


#include <Wire.h>

// MPU-6050のアドレス、レジスタ設定値
#define MPU6050_WHO_AM_I 0x75    // Read Only
#define MPU6050_PWR_MGMT_1 0x6B  // Read and Write
#define MPU_ADDRESS 0x68

float pitch_init, roll_init;

void get_gyro(float *, float *);

void setup() {
  Wire.begin();

  // 出力用
  Serial.begin(115200);

  // 初回の読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_WHO_AM_I);  // MPU6050_PWR_MGMT_1
  Wire.write(0x00);
  Wire.endTransmission();

  // 動作モードの読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);  // MPU6050_PWR_MGMT_1レジスタの設定
  Wire.write(0x00);
  Wire.endTransmission();
  
  delay(1000);

  get_gyro(&pitch_init, &roll_init);
}

void loop() {
  float pitch_raw, roll_raw;
  get_gyro(&pitch_raw, &roll_raw);
  float pitch = pitch_raw - pitch_init;
  float roll = roll_raw - roll_init;
  /*Serial.print(temp);
  Serial.print(",");*/
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  Serial.print("\n");
  delay(1000);
}

void get_gyro(float *pitch, float *roll) {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);
  while (Wire.available() < 14)
    ;
  int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, Temperature;

  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  Temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

  // 加速度値を分解能で割って加速度(G)に変換する
  float acc_x = axRaw / 16384.0;
  float acc_y = ayRaw / 16384.0;
  /*float acc_z = azRaw / 16384.0;

  // 温度
  double temp = Temperature / 340.0 + 35.0;

  // 角速度値を分解能で割って角速度(degrees per sec)に変換する
  float gyro_x = gxRaw / 131.0;  // FS_SEL_0 131 LSB / (°/s)
  float gyro_y = gyRaw / 131.0;
  float gyro_z = gzRaw / 131.0;*/

  // ピッチ・ロールに変換
  *pitch = acc_x * (-90.0);
  *roll = acc_y * (-90.0);
}

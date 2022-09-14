#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial TWE(5, 6); // RX, TX

void AE_HX711_Init(void);
void AE_HX711_Reset(void);
long AE_HX711_Read(void);
long AE_HX711_Averaging(long adc,char num);
float AE_HX711_getGram(char num);

// ピンの設定
//  DAT
#define pin_dout  8
//  CLK
#define pin_slk   9
#define LED 13

// 定格出力 [V]
#define OUT_VOL   0.002f
// 定格容量 [g]
#define LOAD      20000.0f
// 送るデータの文字数(16進数)
#define DATA_SIZE 8
// (MOD)進数でデータを送る
#define MOD 10

// 変数
float offset, data;
int val = 0; // 送信する値
int a, count; // 10進数にするのに使う
int i;
char DATA_str[DATA_SIZE]; // 

void setup() {
  TWE.begin(115200);
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // 送信確認用
  AE_HX711_Init();
  AE_HX711_Reset();
  offset = AE_HX711_getGram(30); 
}

void loop() { 
  data = AE_HX711_getGram(5);
  for (i = 0; i < DATA_SIZE; i++) DATA_str[i] = '0';
  val = int (data - offset);
  //val++;
  Serial.println(val);
  //sprintf(DATA,"%d", val);
  
  digitalWrite(LED, HIGH);

  // 16進数の文字列に変換(クソ)
  if (val < 0) {
    a = -1 * val;
    DATA_str[0] = '1';
  }
  else {
    a = val;
  }
  count = DATA_SIZE - 1;
  while (a != 0 && count >= 0) {
    if (a % MOD == 0) DATA_str[count] = '0';
    else if (a % MOD == 1) DATA_str[count] = '1';
    else if (a % MOD == 2) DATA_str[count] = '2';
    else if (a % MOD == 3) DATA_str[count] = '3';
    else if (a % MOD == 4) DATA_str[count] = '4';
    else if (a % MOD == 5) DATA_str[count] = '5';
    else if (a % MOD == 6) DATA_str[count] = '6';
    else if (a % MOD == 7) DATA_str[count] = '7';
    else if (a % MOD == 8) DATA_str[count] = '8';
    else if (a % MOD == 9) DATA_str[count] = '9';
    /*else if (a % MOD == 10) DATA_str[count] = 'A';
    else if (a % MOD == 11) DATA_str[count] = 'B';
    else if (a % MOD == 12) DATA_str[count] = 'C';
    else if (a % MOD == 13) DATA_str[count] = 'D';
    else if (a % MOD == 14) DATA_str[count] = 'E';
    else DATA_str[count] = 'F';*/
    a = a / MOD;
    count--;
  }
  // 送信
  for (i = 0; i < DATA_SIZE; i++) TWE.write(DATA_str[i]);
  
  digitalWrite(LED, LOW);
  delay(500);
}


void AE_HX711_Init(void)
{
  pinMode(pin_slk, OUTPUT);
  pinMode(pin_dout, INPUT);
}

void AE_HX711_Reset(void)
{
  digitalWrite(pin_slk,1);
  delayMicroseconds(100);
  digitalWrite(pin_slk,0);
  delayMicroseconds(100); 
}

long AE_HX711_Read(void)
{
  long data=0;
  while(digitalRead(pin_dout)!=0);
  delayMicroseconds(10);
  for(int i=0;i<24;i++)
  {
    digitalWrite(pin_slk,1);
    delayMicroseconds(5);
    digitalWrite(pin_slk,0);
    delayMicroseconds(5);
    data = (data<<1)|(digitalRead(pin_dout));
  }
  //Serial.println(data,HEX);   
  digitalWrite(pin_slk,1);
  delayMicroseconds(10);
  digitalWrite(pin_slk,0);
  delayMicroseconds(10);
  return data^0x800000; 
}


long AE_HX711_Averaging(long adc,char num)
{
  long sum = 0;
  for (int i = 0; i < num; i++) sum += AE_HX711_Read();
  return sum / num;
}

float AE_HX711_getGram(char num)
{
  #define HX711_R1  20000.0f
  #define HX711_R2  8200.0f
  #define HX711_VBG 1.25f
  #define HX711_AVDD      4.2987f//(HX711_VBG*((HX711_R1+HX711_R2)/HX711_R2))
  #define HX711_ADC1bit   HX711_AVDD/16777216 //16777216=(2^24)
  #define HX711_PGA 128
  #define HX711_SCALE     (OUT_VOL * HX711_AVDD / LOAD *HX711_PGA)
  
  float data;

  data = AE_HX711_Averaging(AE_HX711_Read(),num)*HX711_ADC1bit; 
  data =  data / HX711_SCALE;

  return data;
}

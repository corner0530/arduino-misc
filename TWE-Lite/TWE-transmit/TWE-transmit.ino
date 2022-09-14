#include <SoftwareSerial.h>
SoftwareSerial TWE(2, 3); // RX, TX

#define LED 13
#define DATA_SIZE 6
#define MOD 16

int val = 0;  // 送信する値(テスト用)
int a, count;
char DATA[DATA_SIZE] = {'0', '0', '0', '0', '0', '0'}; // 送るデータ

void setup() {
  TWE.begin(38400);
  Serial.begin(38400);
  pinMode(LED, OUTPUT);
}

void loop() {
  //while (!TWE.available()) {}
  digitalWrite(LED, HIGH); // 確認用LEDをつける
  // 送信始め
  /*char DATA_START[5] = {':', '7', '8', '0', '1'};
  for (int i = 0; i < 5; i++) TWE.write(DATA_START[i]);
*/
  val = (val + 1) % 65536; // 1ずつ増えて256に達したら0
  Serial.println(val);
  TWE.println(val);
  // データを送信

  // 16進数で送信
  /*a = val;
  count = DATA_SIZE - 1;
  while (a != 0 && count >= 0) {
    if (a % MOD == 0) DATA[count] = '0';
    else if (a % MOD == 1) DATA[count] = '1';
    else if (a % MOD == 2) DATA[count] = '2';
    else if (a % MOD == 3) DATA[count] = '3';
    else if (a % MOD == 4) DATA[count] = '4';
    else if (a % MOD == 5) DATA[count] = '5';
    else if (a % MOD == 6) DATA[count] = '6';
    else if (a % MOD == 7) DATA[count] = '7';
    else if (a % MOD == 8) DATA[count] = '8';
    else if (a % MOD == 9) DATA[count] = '9';
    else if (a % MOD == 10) DATA[count] = 'A';
    else if (a % MOD == 11) DATA[count] = 'B';
    else if (a % MOD == 12) DATA[count] = 'C';
    else if (a % MOD == 13) DATA[count] = 'D';
    else if (a % MOD == 14) DATA[count] = 'E';
    else DATA[count] = 'F';
    a = a / MOD;
    count--;
  }*/
  for (int i = 0; i < DATA_SIZE; i++) TWE.write(DATA[i]);

/*  // 送信終わり
  char DATA_END[3] = {'X', '\r', '\n'};
  for (int i = 0; i < 3; i++) TWE.write(DATA_END[i]);
*/
  digitalWrite(LED, LOW); // 確認用LEDを消す
  delay(250);
}

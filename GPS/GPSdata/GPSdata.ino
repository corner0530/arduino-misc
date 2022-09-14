#include <SoftwareSerial.h>

// rxPin = 11  txPin = 10
SoftwareSerial GPSSerial(11, 10);

// NMEAの緯度経度を「度」(DD)の文字列に変換する
String NMEA2DD(float val) {
  int d = val / 100;
  int m = (((val / 100.0) - d) * 100.0) / 60;
  float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
  return String(d + m + s, 6);
}

void setup() {
  GPSSerial.begin(9600);
  Serial.begin(115200);
}

void loop() {
  // 1つのセンテンスを読み込む
  String line = GPSSerial.readStringUntil('\n');

  if (line != "") {
    int index = 0, len = line.length();
    String str = "";

    // StringListの生成(簡易)
    /*
      0:センテンス
      1:時間(UTC)
      2:緯度
      3:経度
      4:GPSの精度
      5:受信衛星数
      6:HDOP
      7:平均海水面からの高度
      8:WGS-84楕円体から平均海水面の高度差
      9:DGPSデータのエイジ(？)
      10:DGPS基準局のID
      11:チェックサム
    */
    String list[30];
    for (int i = 0; i < 30; i++) {
      list[i] = "";
    }

    // 「,」を区切り文字として文字列を配列にする
    for (int i = 0; i < len; i++) {
      if (line[i] == ',') {
        list[index++] = str;
        str = "";
        continue;
      }
      str += line[i];
    }

    // $GPGGAセンテンスのみ読み込む
    if (list[0] == "$GPGGA") {
      // ステータス
      if (list[6] != "0") {
        // 現在時刻
        // UTC時刻から日本の標準時刻に変換する(GMT+9:00)
        int hh = (list[1].substring(0, 2).toInt()) + 9;
        if (hh > 24) hh = hh - 24;
        int mm = list[1].substring(2, 4).toInt(),
            ss = list[1].substring(4, 6).toInt();
        char time[16];
        snprintf(time, sizeof(time), "%02d:%02d:%02d", hh, mm, ss);
        Serial.print(time);

        // 緯度(*10e6)
        Serial.print(" latitude:");
        int period_lati = list[2].indexOf('.');
        long lati_raw = list[2].substring(0, period_lati).toInt() * 10000 +
                        list[2].substring(period_lati + 1).toInt();
        // Serial.print(' ');
        // Serial.print(lati_raw);
        long latitude =
            lati_raw / 1000000 * 1000000 + (lati_raw % 1000000) * 100 / 60;
        Serial.print(' ');
        Serial.print(latitude);

        // 経度(*10e6)
        Serial.print(" longitude:");
        int period_longi = list[4].indexOf('.');
        long longi_raw = list[4].substring(0, period_longi).toInt() * 10000 +
                         list[4].substring(period_longi + 1).toInt();
        // Serial.print(' ');
        // Serial.print(longi_raw);
        long longitude =
            longi_raw / 1000000 * 1000000 + (longi_raw % 1000000) * 100 / 60;
        Serial.print(' ');
        Serial.print(longitude);

        // 海抜(*10)
        Serial.print(" altitude:");
        int period_alti = list[9].indexOf('.');
        String alti_str = list[9].substring(0, period_alti);
        alti_str.concat(list[9].substring(period_alti + 1, period_alti + 2));
        int altitude = alti_str.toInt();
        Serial.print(altitude);
        Serial.print("0cm");
      } else {
        Serial.print("測位できませんでした。");
      }

      Serial.println("");
    }
  }
}

#include <M5Stack.h>

#define TRIG 2
#define ECHO 5

float times;  //超音波の往復時間 [us]
float distance; //物体距離[cm]
float sound_Vel = 340;  //音速 340 [m/s]

void setup() {
  M5.begin();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // 文字サイズ
  M5.Lcd.setTextSize(2);
}

void loop() {
  // 画面を黒くする
  M5.Lcd.fillScreen(BLACK);

  // 超音波を発生させる
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);  //Triggerを10usの間High Levelに設定, 基本はLow Level
  digitalWrite(TRIG, LOW); //この後に超音波モジュールから勝手に40kHzで8パルスが送出される
  
  // 超音波を受け取る
  times = pulseIn(ECHO, HIGH); //超音波を送信終了後から受信するまでの時間
  distance = times * 0.017; //times*340/2*(1/1000000)*100でcmに変換: [us]*[m/s]*[s/us]*[cm/m]=[cm]

  // ディスプレイに表示させる
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("distance=");
  M5.Lcd.print(distance);
  M5.Lcd.print("cm\n");
  M5.Lcd.print("ReflectingTime=");
  M5.Lcd.print(times);
  M5.Lcd.print("us");
  delay(1000);
}

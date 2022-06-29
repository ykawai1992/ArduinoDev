//PWMFScan.ino//

//モータ駆動に使用されるPWM信号はPWM周期一定(PWM周波数一定)でデューティー比を変化させるものでした。
//ここではデューティー比50%に保ったまま，PWM周波数を変化させるPWM信号を発生させます。
#include <M5Stack.h>

const uint8_t nBits_forPWM = 8; // PWMに使用するビット数　n=1～16[bit]
                            //PWM周波数の最大値 Maxfreq=80000000.0/2^n[Hz]=312500[Hz]
const uint8_t PWM_CH = 2;   // PWMチャンネル
const uint8_t PWM_PIN = 2;  // PWM出力に使用するGPIO PIN番号
const int PWM_Values = 256; //デューティ　デューティー比50%固定
                            //MaxDuty=2^n  DutyRatio = Duty/MaxDuty
const double PWM_Frequencies[] = {2000.0, 4000.0, 6000.0, 8000.0, 10000.0, 12000.0, 14000.0};
                            // PWM周波数 Maxfreq=80000000.0/2^n[Hz]
const int nPWM_Frequencies = sizeof(PWM_Frequencies)/sizeof(double);

int freqIndex = 0;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("PWM Test");
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.printf("freqIndex = %d\n", freqIndex);
  M5.Lcd.printf("PWM frequency = %.1f  \n", PWM_Frequencies[freqIndex]);

  pinMode(PWM_PIN, OUTPUT); 

  // チャンネルと周波数の分解能を設定
  ledcSetup(PWM_CH, PWM_Frequencies[freqIndex], nBits_forPWM);
  // PWM出力ピンとチャンネルの設定
  ledcAttachPin(PWM_PIN, PWM_CH);
  // デューティーの設定と出力開始
  ledcWrite(PWM_CH, PWM_Values);
}

void loop() {
  static int ValueIndex = 0;
  M5.update();

  if (M5.BtnA.wasPressed()) {
    freqIndex++;
    if (nPWM_Frequencies<=freqIndex) freqIndex = 0;
    M5.Speaker.tone(880, 200); //Peett
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.printf("freqIndex = %d\n", freqIndex);
    M5.Lcd.printf("PWM frequency = %.1f  \n", PWM_Frequencies[freqIndex]);
    // チャンネルと周波数を更新
    ledcSetup(PWM_CH, PWM_Frequencies[freqIndex], nBits_forPWM);
    // 出力再開
    ledcWrite(PWM_CH, PWM_Values);
  }
}

// モーター動作のサンプルプログラム3
#include <Zumo32U4.h>
#define MaxSpeed 200      // モーターの最大速度

Zumo32U4ButtonA buttonA;  // ボタンAのオブジェクト変数
Zumo32U4Motors motors;    // モーターのオブジェクト変数
Zumo32U4LCD lcd;          // LCDのオブジェクト変数

void setup(){
  lcd.clear();
  lcd.print("Press A");
}

void loop(){
  // ボタンAが押されたら加減速
  bool buttonPress = buttonA.getSingleDebouncedPress();
  if(buttonPress){
    // 緑LEDを点灯し最大速度まで速度をインクリメント
    ledGreen(1);  // LED ON
    for(int speed = 0; speed < MaxSpeed; speed++){
      motors.setSpeeds(speed, speed);
      delay(5);   // 5/1000[s]待つ
    }
    ledGreen(0);  // LED OFF
    // 赤LEDを点灯し0まで速度をデクリメント
    ledRed(1);    // LED ON
    for(int speed = MaxSpeed; speed >= 0; speed--){
      motors.setSpeeds(speed, speed);
      delay(5);   // 5/1000[s]待つ
    }
    ledRed(0);    // LED OFF
  }
}

// モーター動作のサンプルプログラム1　
#include <Zumo32U4.h>
#define MaxSpeed 100      // モーターの最大速度

Zumo32U4Motors  motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA buttonA;  // ボタンAのオブジェクト変数
Zumo32U4ButtonB buttonB;  // ボタンBのオブジェクト変数
Zumo32U4ButtonC buttonC;  // ボタンCのオブジェクト変数
Zumo32U4LCD lcd;          // LCDのオブジェクト変数

int buttonB_state = 0;    // ボタンBの状態
int buttonC_state = 0;    // ボタンCの状態

void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}

void loop(){
  // ボタンBを押すと前進
  buttonB_state = buttonB.isPressed();
  if(buttonB_state == 1){
    motors.setSpeeds(MaxSpeed, MaxSpeed);
  }
  // ボタンCを押すと停止
  buttonC_state = buttonC.isPressed();
  if(buttonC_state == 1){
    motors.setSpeeds(0, 0);
  }
}

// モーター動作のサンプルプログラム5
#include <Zumo32U4.h>
#define MaxSpeed 200      // モーターの最大速度
Zumo32U4Motors  motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA buttonA;  // ボタンAのオブジェクト変数
Zumo32U4ButtonB buttonB;  // ボタンBのオブジェクト変数
Zumo32U4LCD lcd;          // LCDのオブジェクト変数
void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}
void loop(){
  // ボタンAを押すと停止
  int buttonA_state = buttonA.isPressed();
  if(buttonA_state == 1){
    motors.setSpeeds(0, 0);
  }
  // ボタンBを押すと右旋回
  int buttonB_state = buttonB.isPressed();
  if(buttonB_state){
    ledGreen(1);
    for(int speed = 0; speed <= MaxSpeed; speed++){
      motors.setLeftSpeed(speed);   // 左モーターを加速
      motors.setRightSpeed(-speed); // 右モーターを減速
      delay(5);
    }
    ledGreen(0);
    ledRed(1);
    for(int speed = MaxSpeed; speed >= 0; speed--){
      motors.setLeftSpeed(speed);   // 左モーターを減速
      motors.setRightSpeed(-speed); // 右モーターを加速
      delay(5);
    }
    ledRed(0);
    buttonB_state = 0;
  }
}

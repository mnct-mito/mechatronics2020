// モーター動作のサンプルプログラム6
// 前進と旋回動作の組み合わせ
#include <Zumo32U4.h>
#define MaxSpeed 200      // モーターの最大速度
Zumo32U4LCD lcd;          // LCDのオブジェクト変数
Zumo32U4ButtonA buttonA;  // ボタンAのオブジェクト変数
Zumo32U4Motors motors;    // モーターのオブジェクト変数
void setup(){
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press A");
}
void loop(){
  bool buttonPress = buttonA.getSingleDebouncedPress();
  // ボタンAが押されたら1度だけ以下を実行
  if (buttonPress) {
    ledYellow(1);
    for(int loop=0; loop<4; loop++){
      // 前進（加速）
      for(int speed = 0; speed < MaxSpeed; speed++){
        motors.setSpeeds(speed, speed);
        delay(5);
      }
      // 前進（減速）
      for(int speed = MaxSpeed; speed >= 0; speed--){
        motors.setSpeeds(speed, speed);
        delay(5);
      }
      // 左旋回（加速）
      for(int speed = 0; speed < MaxSpeed; speed++){
        motors.setSpeeds(speed, -speed);
        delay(2);
      }
      // 左旋回（減速）
      for(int speed = MaxSpeed; speed >= 0; speed--){
        motors.setSpeeds(speed, -speed);
        delay(2);
      }
    }
    ledYellow(0);
  }
}

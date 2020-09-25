// モーター動作のサンプルプログラム2　
#include <Zumo32U4.h>

Zumo32U4Motors  motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA buttonA;  // ボタンAのオブジェクト変数
Zumo32U4ButtonB buttonB;  // ボタンBのオブジェクト変数
Zumo32U4ButtonC buttonC;  // ボタンCのオブジェクト変数
Zumo32U4LCD lcd;          // LCDのオブジェクト変数

int motor_speed = 50;     // モーターの回転速度
int buttonA_state = 0;    // ボタンAの状態
int buttonB_state = 0;    // ボタンBの状態
int buttonC_state = 0;    // ボタンCの状態

void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}

void loop(){
  // ボタンAを押すと前進方向にモーター回転開始
  buttonA_state = buttonA.isPressed();
  while(buttonA_state == 1){
    motors.setSpeeds(motor_speed, motor_speed);
    // ボタンBを押すとモーター加速
    if(buttonB.getSingleDebouncedPress()){
      motor_speed += 10;
    }
    // ボタンを押すとモーター減速
    if(buttonC.getSingleDebouncedPress()){
      motor_speed -= 10;
    }
  }
}

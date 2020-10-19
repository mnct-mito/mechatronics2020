#include<Zumo32U4.h> 
Zumo32U4Encoders  encoders;
Zumo32U4Motors    motors;
Zumo32U4ButtonA   buttonA;
Zumo32U4LCD       lcd; 
void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
}
void loop(){
  // ボタンAを押すとクランク走行のような動作
  int buttonA_state = buttonA.isPressed();
  delay(50);
  if(buttonA_state == 1){
    buttonA_state = 0;
    unRegMoveSteer(200, 0, 1800);   // 前
    unRegMoveSteer(200, 50, 900);   // 右
    unRegMoveSteer(200, 0, 900);    // 前
    unRegMoveSteer(200, -50, 900);  // 左
    unRegMoveSteer(200, 0, 1800);   // 前
    motors.setSpeeds(0, 0);
  }
}
// 以下の関数のプログラムは以下のサイトからの引用：
// http://www.abrowndesign.com/2016/10/21/zumo-32u4-unregulated-unsynchronized-motor-steer-block/
void unRegMoveSteer(int targetSpeed, int turnDirection, int enCounts) {
  int countsLeft  = encoders.getCountsAndResetLeft();
  int countsRight = encoders.getCountsAndResetRight();
  int targetSpeedLeft;
  int targetSpeedRight;
  if(turnDirection > 0){
    targetSpeedLeft  = targetSpeed;
    targetSpeedRight = targetSpeed * (turnDirection - 50) / (-50.0);
  }else{
    targetSpeedRight = targetSpeed;
    targetSpeedLeft  = targetSpeed * (turnDirection + 50) / (50.0);
  }
  motors.setSpeeds(targetSpeedLeft, targetSpeedRight);
  if(turnDirection >= 0){
    do{
      countsLeft = encoders.getCountsLeft();
    }while(abs(countsLeft) < abs(enCounts));
  }else{
    do{
      countsRight = encoders.getCountsRight();      
    } while (abs(countsRight) < abs(enCounts));
  }    
} 

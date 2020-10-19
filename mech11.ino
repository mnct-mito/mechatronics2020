#include <Zumo32U4.h>
#define MaxSpeed 200
Zumo32U4Encoders  encoders;
Zumo32U4Motors    motors;
Zumo32U4ButtonA   buttonA;
Zumo32U4LCD       lcd;
void setup( ) {
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press A");
}
void loop( ){
  int countsLeft, countsRight;
  bool buttonPress = buttonA.getSingleDebouncedPress();
  // ボタンAが押されたら1度だけ以下を実行
  if (buttonPress) {
    ledYellow(1);
    delay(1000);
    for(int loop=0; loop<2; loop++){
      // 加速→一定速度
      for(int speed = 0; speed <= MaxSpeed; speed++){
        motors.setSpeeds( speed, speed );delay( 10 );
      }
      // 前方向に約25cm進む
      countsLeft  = encoders.getCountsAndResetLeft( );  // 左の値取得とリセット
      countsRight = encoders.getCountsAndResetRight( ); // 右の値取得とリセット
      do{
        countsLeft  = encoders.getCountsLeft( );  // 左
        countsRight = encoders.getCountsRight( ); // 右
      }while(countsLeft < 1820); // 値は要調整
      // 減速→停止
      ledRed(1);
      for(int speed = MaxSpeed; speed >= 0; speed--){
        motors.setSpeeds( speed, speed ); delay( 10 );
      }
      ledRed(0);
      // 約90度右旋回（Uターン）
      countsLeft  = encoders.getCountsAndResetLeft( );  // 左の値取得とリセット
      countsRight = encoders.getCountsAndResetRight( ); // 右の値取得とリセット
      motors.setSpeeds( 200, 0 );
      do{
        countsLeft  = encoders.getCountsLeft( );  // 左
        countsRight = encoders.getCountsRight( ); // 右
      }while(countsLeft < 2600); // 値は要調整
      motors.setSpeeds( 0, 0 );
    }
    ledYellow(0);
  }
}

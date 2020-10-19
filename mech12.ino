// エンコーダーを利用したモーターの回転速度制御
#include <Zumo32U4.h>
Zumo32U4Encoders  encoders; // エンコーダーのオブジェクト変数
Zumo32U4Motors    motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA   buttonA;  // ボタンAのオブジェクト変数
Zumo32U4ButtonB   buttonB;  // ボタンBのオブジェクト変数
Zumo32U4ButtonC   buttonC;  // ボタンCのオブジェクト変数
Zumo32U4LCD       lcd;      // LCDのオブジェクト変数
// パラメータ
#define Speed     100       // モーターの回転速度
#define Kp        0.1       // このパラメータを変更する
//
int motor_speed = Speed;  // モーターの回転速度
int buttonA_state = 0;    // ボタンAの状態
int buttonB_state = 0;    // ボタンBの状態
int buttonC_state = 0;    // ボタンCの状態
void setup(){
  Serial.begin(115200);     // シリアルポートの設定
  lcd.clear();
}
void loop(){
  int currentSpeedLeft  = motor_speed;
  int currentSpeedRight = motor_speed;
  motors.setSpeeds(0, 0);
  // ボタンAを押すと前進方向にモーター回転開始
  buttonA_state = buttonA.isPressed();
  delay(200);
  int countsLeft  = encoders.getCountsAndResetLeft();
  int countsRight = encoders.getCountsAndResetRight();
  while(buttonA_state == 1){
    motors.setSpeeds(currentSpeedLeft, currentSpeedRight);
    countsLeft  = encoders.getCountsLeft();
    countsRight = encoders.getCountsRight();
    Serial.print(currentSpeedLeft);
    Serial.print(",");
    Serial.print(currentSpeedRight);
    Serial.println("");
    lcd.clear();
    lcd.print(currentSpeedLeft);
    lcd.gotoXY(5, 0);
    lcd.print(currentSpeedRight);
    currentSpeedRight = motor_speed + Kp * (countsLeft - countsRight);
    motors.setSpeeds(currentSpeedLeft, currentSpeedRight);
    // ボタンBを押すと左モーター加速
    if(buttonB.getSingleDebouncedPress()){
      currentSpeedLeft += 10;
    }
    // ボタンを押すと左モーター減速
    if(buttonC.getSingleDebouncedPress()){
      currentSpeedLeft -= 10;
    }
  }
}

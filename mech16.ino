#include <Zumo32U4.h>
#define QTR_THRESHOLD     1000 // ラインセンサの閾値
#define REVERSE_SPEED     200  // 後退スピード
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200  // 後退時間
#define TURN_DURATION     300  // 旋回時間
Zumo32U4LCD         lcd;
Zumo32U4ButtonA     buttonA;
Zumo32U4Motors      motors;
Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3];
void waitForButtonPres(){
  ledYellow(1);
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  ledYellow(0);
  delay(1000);
}
void setup(){
  lineSensors.initThreeSensors();
  waitForButtonPres();
}
void loop(){
  if(buttonA.isPressed()){
    // ボタンAが押されたら動作を停止する
    motors.setSpeeds(0, 0);
    buttonA.waitForRelease();
    waitForButtonPres();
  }
  lineSensors.read(lineSensorValues);
  if(lineSensorValues[0] < QTR_THRESHOLD){
    // 左側のセンサがラインを検出したら，後退し右側に旋回する
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }else if(lineSensorValues[2] < QTR_THRESHOLD){
    // 右側のセンサがラインを検出したら，後退し左側に旋回する
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }else{
    // それ以外は直進する
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}

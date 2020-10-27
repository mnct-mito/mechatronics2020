// 本サンプルプログラムは以下のコードを授業用に改編したものである
// https://github.com/pvcraven/zumo_32u4_examples/tree/master/TurnExample
// Copyright (c) 2016 Paul V Craven
// Released under the MIT license.
// see https://opensource.org/licenses/MIT

#include <Zumo32U4.h>
#include <Wire.h>

uint32_t turnAngle      = 0;
int16_t  turnRate;
int16_t  gyroOffset;
uint16_t gyroLastUpdate = 0;
int turnSpeed           = 150;
int motorSpeed          = 250;

void turnSensorSetup();
void turnSensorReset();
void turnSensorUpdate();

Zumo32U4LCD               lcd;
Zumo32U4ProximitySensors  proxSensors;
Zumo32U4Encoders          encoders;
Zumo32U4ButtonA           buttonA;
Zumo32U4Motors            motors;
LSM303                    lsm303;
L3G                       gyro;

void turnSensorSetup(){
  Wire.begin();
  gyro.init();
  gyro.writeReg(L3G::CTRL1, 0b11111111);
  gyro.writeReg(L3G::CTRL4, 0b00100000);
  gyro.writeReg(L3G::CTRL5, 0b00000000);
  lcd.clear();
  lcd.print(F("Gyro cal"));
  ledYellow(1);
  delay(500);
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++){
    while(!gyro.readReg(L3G::STATUS_REG) & 0x08);
    gyro.read();
    total += gyro.g.z;
  }
  ledYellow(0);
  gyroOffset = total / 1024;
}

void turnSensorReset(){
  gyroLastUpdate = micros();
  turnAngle = 0;
}

void turnSensorUpdate(){
  gyro.read();
  turnRate = gyro.g.z - gyroOffset;
  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;
  int32_t d = (int32_t)turnRate * dt;
  turnAngle += (int64_t)d * 14680064 / 17578125;
}

void turnRight(int degrees) {
  turnSensorReset();
  motors.setSpeeds(turnSpeed, -turnSpeed);
  int angle = 0;
  do {
    delay(1);
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;
    lcd.gotoXY(0, 0);
    lcd.print(angle);
    lcd.print(" ");
  } while (angle > -degrees);
  motors.setSpeeds(0, 0);
}

void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
  lcd.gotoXY(0, 0);
  lcd.print("Press A");
}

void loop( ){
  int  countsLeft, countsRight;
  bool buttonPress = buttonA.getSingleDebouncedPress();
  // ボタンAが押されたら1度だけ以下を実行
  if (buttonPress) {
    ledYellow(1);
    delay(1000);
    for(int loop=0; loop<4; loop++){
      // 前方向に進む
      countsLeft  = encoders.getCountsAndResetLeft( );  // 左の値取得とリセット
      countsRight = encoders.getCountsAndResetRight( ); // 右の値取得とリセット
      // 加速→一定速度
      for(int speed = 0; speed <= motorSpeed; speed++){
        motors.setSpeeds( speed, speed );delay( 10 );
      }
      do{
        countsLeft  = encoders.getCountsLeft( );  // 左
        countsRight = encoders.getCountsRight( ); // 右
      }while(countsLeft < 100); // 値は要調整
      // 減速→停止
      ledRed(1);
      for(int speed = motorSpeed; speed >= 0; speed--){
        motors.setSpeeds( speed, speed ); delay( 10 );
      }
      ledRed(0);
      // 約90度右旋回
      delay(10);
      turnRight(90);
    }
    ledYellow(0);
  }
}

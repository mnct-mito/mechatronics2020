// 本サンプルプログラムは以下のコードを授業用に改編したものである
// https://github.com/pvcraven/zumo_32u4_examples/tree/master/GyroSensorExample
// Copyright (c) 2016 Paul V Craven
// Released under the MIT license.
// see https://opensource.org/licenses/MIT

#include <Zumo32U4.h>
#include <Wire.h>

uint32_t turnAngle = 0;
int16_t  turnRate;
int16_t  gyroOffset;
uint16_t gyroLastUpdate = 0;

void turnSensorSetup();
void turnSensorReset();
void turnSensorUpdate();

Zumo32U4LCD lcd;
L3G gyro;

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

int32_t getAngle() {
  //リセット後のセンサ値を角度に変換
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}

void setup() {
  turnSensorSetup();
  delay(500);
  turnSensorReset();
  lcd.clear();
}

void loop() {
  turnSensorUpdate();
  int32_t angle = getAngle();
  lcd.gotoXY(0, 0);
  lcd.print(angle);
  lcd.print(" ");
}

#include <Zumo32U4.h>
Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3];
void setup() {
  lineSensors.initThreeSensors();
  lcd.clear( );
}
void loop() {
  lineSensors.read(lineSensorValues);
  // 1つ目
  lcd.gotoXY(0, 0);
  lcd.print(lineSensorValues[0] / 10);
  lcd.print("  ");
  // 2つ目
  lcd.gotoXY(5, 0);
  lcd.print(lineSensorValues[1] / 10);
  lcd.print("  ");
  // 3つ目
  lcd.gotoXY(0, 1);
  lcd.print(lineSensorValues[2] / 10);
  lcd.print("  ");
  delay(250);
}

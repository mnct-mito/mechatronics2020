// メカトロニクス演習2 第1回 サンプルプログラム

#include <Zumo32U4.h>
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LCD lcd;
int val = 0;     // ボタンの状態
int old_val = 0; // ボタンの古い状態
int state = 0;   // LEDの状態
void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}
void loop(){
  val = buttonB.isPressed();
  if((val == 1) && (old_val == 0)){
    state = 1 - state;
    delay(10);
  }
  old_val = val;
  if(state == 1){
    ledYellow(1);
  }else{
    ledYellow(0);
  }
}

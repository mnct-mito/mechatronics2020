// メカトロニクス演習2 第1回 サンプルプログラム
// ボタンBでLEDのON/OFFを制御するプログラムの一例

#include <Zumo32U4.h>
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LCD lcd;
int current_button_state = 0;  // ボタンの現在の状態
int old_button_state = 0;      // ボタンの古い状態
int led_state = 0;             // LEDの状態
void setup(){
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
  lcd.print(F("Press B"));
}
void loop(){
  current_button_state = buttonB.isPressed();
  if((current_button_state == 1) && (old_button_state == 0)){
    led_state = 1 - led_state;
    delay(10);
  }
  old_button_state = current_button_state;
  if(led_state == 1){
    ledYellow(1);
  }else{
    ledYellow(0);
  }
}
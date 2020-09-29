// エンコーダーの値を取得するサンプルプログラム1
#include <Zumo32U4.h>
Zumo32U4Encoders  encoders; // エンコーダーのオブジェクト変数
Zumo32U4Motors    motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA   buttonA;  // ボタンAのオブジェクト変数
Zumo32U4LCD       lcd;      // LCDのオブジェクト変数
void setup(){
  lcd.clear();
}
void loop(){
  int countsLeft, countsRight;  // エンコーダーの値（左右）を代入する変数の宣言
  lcd.gotoXY(0, 1);             // 文字列の始まりをLCDの2行目の左端に
  lcd.print("Press A");         // LCD画面に「Press A」を表示
  buttonA.waitForButton();      // ボタンAが押されるのを待つ
  countsLeft  = encoders.getCountsAndResetLeft();  // 左エンコーダーの値を初期化・取得
  countsRight = encoders.getCountsAndResetRight(); // 右エンコーダーの値を初期化・取得
  delay(500);                 // 0.5s（500ms）待つ
  motors.setSpeeds(200, 200); // 左右のモーターの回転数を200に設定
  do{
    countsLeft  = encoders.getCountsLeft();  // 左エンコーダーの値を取得
    countsRight = encoders.getCountsRight(); // 右エンコーダーの値を取得
    lcd.clear();
    lcd.print(countsLeft);    // 左エンコーダーの値を表示
    lcd.gotoXY(4, 0);
    lcd.print(countsRight);   // 右エンコーダーの値を表示
  }while(countsLeft < 900 && countsRight < 900);  // 条件を満たす間繰り返す
  motors.setSpeeds(0, 0);   
}

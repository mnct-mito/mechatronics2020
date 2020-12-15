// エンコーダーの値を取得するサンプルプログラム1
// メカトロニクス演習2第3回サンプルプログラム1の改良
#include <Zumo32U4.h>
Zumo32U4Encoders  encoders; // エンコーダーのオブジェクト変数
Zumo32U4Motors    motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA   buttonA;  // ボタンAのオブジェクト変数
Zumo32U4LCD       lcd;      // LCDのオブジェクト変数

void setup(){
  lcd.clear();
}

void move(int Speed_L, int Speed_R, int E_Counter){
  int countsLeft, countsRight;  // エンコーダーの値（左右）を代入する変数の宣言
  delay(500); // 0.5s（500ms）待つ  不要であればコメントアウトする
  countsLeft  = encoders.getCountsAndResetLeft(); // 左エンコーダーの値を初期化・取得
  countsRight = encoders.getCountsAndResetRight();  // 右エンコーダーの値を初期化・取得
  motors.setSpeeds(Speed_L, Speed_R); // 左右のモーターの回転数を200に設定
  do{
    countsLeft  = encoders.getCountsLeft();  // 左エンコーダーの値を取得
    countsRight = encoders.getCountsRight(); // 右エンコーダーの値を取得
    lcd.clear();
    lcd.print(countsLeft);  // 左エンコーダーの値を表示
    lcd.gotoXY(4, 0);
    lcd.print(countsRight); // 右エンコーダーの値を表示
  }while(abs(countsLeft) < E_Counter && abs(countsRight) < E_Counter);  // 条件を満たす間繰り返す
  motors.setSpeeds(0, 0);
}

void loop(){
  lcd.gotoXY(0, 1); // 文字列の始まりをLCDの2行目の左端に
  lcd.print("A Start"); // LCD画面に「A Start」を表示
  buttonA.waitForButton();  // ボタンAが押されるのを待つ
  move(200, 200, 900);
}
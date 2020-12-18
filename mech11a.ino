// エンコーダーを利用したロボット動作のサンプルプログラム1
// メカトロニクス演習2第4回サンプルプログラム1の改良
#include <Zumo32U4.h>
Zumo32U4Encoders  encoders; // エンコーダーのオブジェクト変数
Zumo32U4Motors    motors;   // モーターのオブジェクト変数
Zumo32U4ButtonA   buttonA;  // ボタンAのオブジェクト変数
Zumo32U4LCD       lcd;      // LCDのオブジェクト変数

void setup(){
  lcd.clear();
}

void move_forward(int Max_Speed, int E_Counter){
  int countsLeft, countsRight;  // エンコーダーの値（左右）を代入する変数の宣言
  delay(500); // 0.5s（500ms）待つ  不要であればコメントアウトする
  countsLeft  = encoders.getCountsAndResetLeft(); // 左エンコーダーの値を初期化・取得
  countsRight = encoders.getCountsAndResetRight();  // 右エンコーダーの値を初期化・取得
  // 加速→一定速度
  for(int speed = 0; speed <= Max_Speed; speed++){
    motors.setSpeeds( speed, speed );delay( 10 );
  }
  // 前方向に約25cm進む
  countsLeft  = encoders.getCountsAndResetLeft( );  // 左の値取得とリセット
  countsRight = encoders.getCountsAndResetRight( ); // 右の値取得とリセット
  do{
      countsLeft  = encoders.getCountsLeft( );  // 左
      countsRight = encoders.getCountsRight( ); // 右
  }while(countsLeft < E_Counter); // 値は要調整
  // 減速→停止
  ledRed(1);
  for(int speed = Max_Speed; speed >= 0; speed--){
    motors.setSpeeds( speed, speed ); delay( 10 );
  }
  ledRed(0);
}

void move_turn(int Speed_L, int Speed_R, int E_Counter){
  int countsLeft, countsRight;  // エンコーダーの値（左右）を代入する変数の宣言
  delay(500); // 0.5s（500ms）待つ  不要であればコメントアウトする
  countsLeft  = encoders.getCountsAndResetLeft(); // 左エンコーダーの値を初期化・取得
  countsRight = encoders.getCountsAndResetRight();  // 右エンコーダーの値を初期化・取得
  // 約90度右旋回（Uターン）
  motors.setSpeeds(Speed_L, Speed_R); // 左右のモーターの回転数を設定
  do{
    countsLeft  = encoders.getCountsLeft( );  // 左
    countsRight = encoders.getCountsRight( ); // 右
  }while(countsLeft < 2600); // 値は要調整
  motors.setSpeeds( 0, 0 ); 
}

void loop(){
  lcd.gotoXY(0, 1); // 文字列の始まりをLCDの2行目の左端に
  lcd.print("A Start"); // LCD画面に「A Start」を表示
  buttonA.waitForButton();  // ボタンAが押されるのを待つ
  move_forward(200, 1820);
  move_turn(200, 0, 2600);
  move_forward(200, 1820);
  move_turn(200, 0, 2600);
}
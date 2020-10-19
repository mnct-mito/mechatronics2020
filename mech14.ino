#include<Zumo32U4.h> 
Zumo32U4Encoders  encoders;
Zumo32U4Motors    motors;
Zumo32U4ButtonA   buttonA;
Zumo32U4LCD       lcd;
#define Speed   200   // 
#define Counts  2700  // 車輪約3回転
#define Kp      1.0   // 
void setup(){
  lcd.clear();
  lcd.print(F("Presss A"));
  buttonA.waitForButton();
}
void loop(){
  int buttonA_state = buttonA.isPressed();
  if(buttonA_state == 1){
    buttonA_state = 0;
    delay(500);
    int L_cSpeed = Speed;
    int R_cSpeed = Speed;
    int L_counts = encoders.getCountsAndResetLeft();
    int R_counts = encoders.getCountsAndResetRight();
    motors.setSpeeds(L_cSpeed, R_cSpeed);
    while(L_counts < Counts && R_cSpeed < Counts){
      L_counts = encoders.getCountsLeft();
      R_counts = encoders.getCountsRight();
      // 左側の状態で右側を更新する
      R_cSpeed = Speed + Kp * (L_counts - R_counts);
      motors.setSpeeds(L_cSpeed, R_cSpeed);
    }
    motors.setSpeeds(0,0);
  }
}

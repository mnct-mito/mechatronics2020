// シリアルプロットを使ったデータの可視化
double angle = 0;
void setup(){
  Serial.begin(115200);
}
void loop(){
  angle++;
  Serial.print(10 * sin(angle / 180 * PI));
  Serial.println("");
  delay(10);
}

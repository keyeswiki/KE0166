/*
  keyes smart turtle robot
  lesson 3.2
  Line Track sensor
  http://www.keyes-robot.com
*/
int L_pin = 11;  //pins of  left line tracking sensor
int M_pin = 7;  //pins of  middle line tracking sensor
int R_pin = 8;  //pins of  right  line tracking sensor
int val_L, val_R, val_M; // 定义三个传感器的变量值
void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  pinMode(L_pin, INPUT); // make the L_pin as an input
  pinMode(M_pin, INPUT); // make the M_pin as an input
  pinMode(R_pin, INPUT); // make the R_pin as an input
  pinMode(9, OUTPUT);
}
void loop() {
  val_L = digitalRead(L_pin);//read the L_pin:
  val_R = digitalRead(R_pin);//read the R_pin:
  val_M = digitalRead(M_pin);//read the M_pin:
  Serial.print("left:");
  Serial.print(val_L);
  Serial.print(" middle:");
  Serial.print(val_M);
  Serial.print(" right:");
  Serial.println(val_R);

  if (val_L == LOW || val_M == LOW || val_R == LOW) //if line tracking sensor 检测到信号
  {
    digitalWrite(9, HIGH);//LED 灯灭
  }
  else//如果left line tracking sensor 没有检测到信号
  {
    digitalWrite(9, LOW);//LED 灯亮
  }
}

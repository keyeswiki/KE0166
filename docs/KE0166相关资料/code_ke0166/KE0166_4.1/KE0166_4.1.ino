/*
  keyes smart turtle robot
  lesson 4.1
  Servo
  http://www.keyes-robot.com
*/
#define servoPin 10  //servo Pin
int pos; //舵机的角度变量
int pulsewidth; //舵机的脉宽变量
void setup() {
  pinMode(servoPin, OUTPUT);  //舵机引脚设置为输出
  procedure(0); //设置舵机的角度为0度
}
void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    procedure(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                   //控制舵机转动的速度
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    procedure(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
}
//控制舵机的函数
void procedure(int myangle) {
  pulsewidth = myangle * 11 + 500;  //计算出脉宽值
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulsewidth);   //高电平持续的时间，就是脉宽
  digitalWrite(servoPin, LOW);
  delay((20 - pulsewidth / 1000));  //周期是20ms，所以低电平持续剩下的时间
}

/*
  keyes smart turtle robot
  lesson 12
  Ultrasonic Follow Robot
  http://www.keyes-robot.com
*/
#include <Matrix.h>
Matrix myMatrix(A4, A5);
uint8_t LedArray1[8] = {0x42, 0xa5, 0x00, 0x00, 0x18, 0x42, 0x3c, 0x00};
uint8_t  LEDArray[8];
int trigPin = 12; //定义TRIG引脚接D12
int echoPin = 13; //定义ECHO引脚接D13
int distance;
int MA = 2; //定义电机A方向控制引脚为D2
int PWMA = 6; //定义电机A速度控制引脚为D6
int MB = 4; //定义电机A方向控制引脚为D4
int PWMB = 5; //定义电机A速度控制引脚为D5

int get_distance() { //超声波测距函数
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //给TRIG引脚至少10us的时间触发
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH) / 58; //检测脉冲宽度，并计算出距离
  delay(10);  //延时10ms
  Serial.print("distance:");  //串口打印出距离
  Serial.print(distance);
  Serial.println("cm");
  return distance;
}

void setup() {
  Serial.begin(9600);  //设置波特率为9600
  pinMode(trigPin, OUTPUT); //定义TRIG为输出模式
  pinMode(echoPin, INPUT); //定义ECHO为输入模式
  pinMode(MA, OUTPUT); //配置电机引脚为输出模式
  pinMode(PWMA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  myMatrix.begin(0x70);
  myMatrix.clear();
  myMatrix.setBrightness(5);//亮度5,范围0~15

}

void loop() {
  for (int i = 0; i < 8; i++)
  {
    LEDArray[i] = LedArray1[i];
    for (int j = 7; j >= 0; j--)
    {
      if ((LEDArray[i] & 0x01) > 0)
        myMatrix.drawPixel(j, i, 1);
      LEDArray[i] = LEDArray[i] >> 1;
    }
  }
  myMatrix.write();
  distance = get_distance(); //调用测距函数

  if (distance < 8 ) {//如果距离小于8
    back();//后退
  }
  else if (distance >= 8 && distance < 13) { //如果距离大于等于8，小于13
    stopp();//停止
  }
  else if (distance >= 13 && distance <= 35 ) { //如果距离大于等于13，小于35
    advance();//跟随
  }
  else {//如果以上都不是
    stopp();//停止
  }
}

void advance() { //小车前进
  digitalWrite(MA, LOW); //电机A正转
  analogWrite(PWMA, 200); //电机A速度为200
  digitalWrite(MB, LOW); //电机B正转
  analogWrite(PWMB, 200); //电机B速度为200
}

void back() { //小车后退
  digitalWrite(MA, HIGH); //电机A反转
  analogWrite(PWMA, 200); //电机A速度为200
  digitalWrite(MB, HIGH); //电机B反转
  analogWrite(PWMB, 200); //电机B速度为200
}

void turnL() { //小车左转
  digitalWrite(MA, HIGH); //电机A反转
  analogWrite(PWMA, 200); //电机A速度为200
  digitalWrite(MB, LOW); //电机B正转
  analogWrite(PWMB, 200); //电机B速度为200
}

void turnR() { //小车右转
  digitalWrite(MA, LOW); //电机A正转
  analogWrite(PWMA, 200); //电机A速度为200
  digitalWrite(MB, HIGH); //电机B反转
  analogWrite(PWMB, 200); //电机B速度为200
}

void stopp() { //小车停止
  analogWrite(PWMA, 0); //电机A速度为0
  analogWrite(PWMB, 0); //电机B速度为0
}

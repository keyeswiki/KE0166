/*
  keyes smart turtle robot
  lesson 13
  Ultrasonic Avoiding Robot
  http://www.keyes-robot.com
*/
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
#include <Matrix.h>
Matrix myMatrix(A4, A5); //定义点阵的引脚在A4,A5
//数组，用于储存图案的数据，可以自己算也可以从取摸工具中得到
uint8_t matrix_heart[8] = {0x66, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00};
uint8_t matrix_smile[8] = {0x42, 0xa5, 0x00, 0x00, 0x18, 0x42, 0x3c, 0x00};
uint8_t matrix_front2[8] = {0x18, 0x24, 0x42, 0x99, 0x24, 0x42, 0x81, 0x00};
uint8_t matrix_back2[8] = {0x00, 0x81, 0x42, 0x24, 0x99, 0x42, 0x24, 0x18};
uint8_t matrix_right2[8] = {0x48, 0x24, 0x12, 0x09, 0x09, 0x12, 0x24, 0x48};
uint8_t matrix_left2[8] = {0x12, 0x24, 0x48, 0x90, 0x90, 0x48, 0x24, 0x12};
uint8_t matrix_stop2[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18};
uint8_t  LEDArray[8];
int trigPin = 12;  //定义TRIG引脚接D12
int echoPin = 13;   //定义ECHO引脚接D13
int distance, distance_l, distance_r;
int MA = 2; //定义电机A方向控制引脚为D2
int PWMA = 6; //定义电机A速度控制引脚为D6
int MB = 4; //定义电机A方向控制引脚为D4
int PWMB = 5; //定义电机A速度控制引脚为D5

void setup ()
{
  Serial.begin(9600);     //测量结果将通过此串口输出至 PC 上的串口监视器
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
  pinMode(echoPin, INPUT);      //设置EchoPin 为输入模式
  pinMode(trigPin, OUTPUT);     //设置超声波数字IO脚模式，OUTPUT为输出
  pinMode(MA, OUTPUT); //配置电机引脚为输出模式
  pinMode(PWMA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  myMatrix.begin(0x70);
  myMatrix.setBrightness(5);//亮度5,范围0~15
  myMatrix.clear();
  myMatrix.write();
  myservo.write(90);  //舵机角度为90
  delay(500);
}

void loop()
{
  distance = get_distance(); //调用测距函数

  if (distance > 0 && distance < 10) { //如果距离小于20且大于0
    stopp();//停止
    myMatrix.clear();
    myMatrix.write();
    matrix_display(matrix_stop2);  //点阵显示停止图案
    delay(100);
    myservo.write(180); //舵机转到180度
    delay(500);
    distance_l = get_distance(); //获取左边的距离
    delay(100);
    myservo.write(0); //舵机转到0度
    delay(500);
    distance_r = get_distance(); //获取右边的距离
    delay(100);
    if (distance_l > distance_r) { //比较距离，如果左边大于右边
      turnL();  //向左转
      myMatrix.clear();
      myMatrix.write();
      matrix_display(matrix_left2);    //点阵显示向左图案
      myservo.write(90);//舵机回到90度
      delay(500);
      myMatrix.clear();
      myMatrix.write();
      matrix_display(matrix_front2);   //点阵显示前进图案

    }
    else { //否则如果右边大于左边
      turnR();//向右转
      myMatrix.clear();
      myMatrix.write();
      matrix_display(matrix_right2);   //显示右转图案
      myservo.write(90);//舵机回到90度
      delay(500);
      myMatrix.clear();
      myMatrix.write();
      matrix_display(matrix_front2);  //点阵显示前进图案
    }
  }

  else { //前方距离小于等于10cm时
    advance();//前进
    myMatrix.clear();
    myMatrix.write();
    matrix_display(matrix_front2);  //点阵显示前进图案
  }

}

int get_distance() {
  int distance = 0;
  digitalWrite(trigPin, LOW);     // 通过Trig/Pin 发送脉冲，触发 HC-SR04 测距，使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);    // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);     // 保持发出超声波信号接口低电平
  distance = pulseIn(echoPin, HIGH) / 58; // 读出脉冲时间,将脉冲时间转化为距离（单位：厘米）
  Serial.println(distance);        //输出距离值
  delay(10);//延时10ms
  return distance;
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

//这个函数用于点阵屏显示
void matrix_display(unsigned char matrix_value[])
{
  for (int i = 0; i < 8; i++)
  {
    LEDArray[i] = matrix_value[i];
    for (int j = 7; j >= 0; j--)
    {
      if ((LEDArray[i] & 0x01) > 0)
        myMatrix.drawPixel(j, i, 1);
      LEDArray[i] = LEDArray[i] >> 1;
    }
  }
  myMatrix.write();
}

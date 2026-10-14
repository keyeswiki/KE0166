/*
  keyes smart turtle robot
  lesson 16
  Multifunctional turtle robot
  http://www.keyes-robot.com
*/
#include <Matrix.h>
#include <IRremote.h>  //导入红外的库
int RECV_PIN = A1; //定义IO口A1
IRrecv irrecv(RECV_PIN);
decode_results results;//声明一个IRremote库函数独有的变量类型
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
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
int trigPin = 12; //定义TRIG引脚接D12
int echoPin = 13; //定义ECHO引脚接D13
int distance, distance_l, distance_r;
int MA = 2; //定义电机A方向控制引脚为D2
int PWMA = 6; //定义电机A速度控制引脚为D6
int MB = 4; //定义电机A方向控制引脚为D4
int PWMB = 5; //定义电机A速度控制引脚为D5
char blue_val;
int IR_val;
int speeds = 200; //初始化速度speeds为200
int L_pin = 11; //定义左边传感器引脚为D11
int M_pin = 7; //定义中间传感器引脚为D7
int R_pin = 8; //定义右边传感器引脚为D8
int L_val, M_val, R_val;

int get_distance() { //超声波测距函数
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //给TRIG引脚至少10us的时间触发
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH) / 58; //检测脉冲宽度，并计算出距离
  delay(20);  //延时20ms
  return distance;
}

void setup() {
  Serial.begin(9600);  //设置波特率为9600
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
  pinMode(trigPin, OUTPUT); //定义TRIG为输出模式
  pinMode(echoPin, INPUT); //定义ECHO为输入模式
  pinMode(L_pin, INPUT); //循迹传感器引脚都配置为输入模式
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);
  pinMode(MA, OUTPUT); //配置电机引脚为输出模式
  pinMode(PWMA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  irrecv.enableIRIn();// 使能红外接收
  myMatrix.begin(0x70);
  myMatrix.setBrightness(5);//亮度5,范围0~15
  myMatrix.clear();
  myMatrix.write();
  matrix_display(matrix_heart);  //点阵显示心形图案
  myservo.write(90);  //舵机角度为90
  delay(500);
}

void loop() {
  if (Serial.available() > 0) { //接收到蓝牙信号
    blue_val = Serial.read(); //接收到的信号赋给blue_val
    Serial.println(blue_val);  //串口监视器显示蓝牙信号
    switch (blue_val) {
      case  'F':  //接收到‘F’前进
        advance();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_front2);   //点阵显示前进图案
        break;

      case  'B':
        back();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_back2);   //点阵显示后退图案
        break;  //接收到‘B’后退

      case  'L':
        turnL();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_left2);    //点阵显示向左图案
        break;  //接收到‘L’左旋转

      case  'R':
        turnR();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_right2);   //显示右转图案
        break;  //接收到‘R’右旋转

      case  'S':
        stopp();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_stop2);  //点阵显示停止图案
        break;  //接收到‘S’停止

      case  'Y':  follow();  break; //接收到‘Y’，进入跟随模式
      case  'U':  avoid();   break;  //接收到‘U’，进入避障模式
      case  'X':  track();   break;  //接收到‘X’，巡黑线模式
    }
  }

  if (irrecv.decode(&results)) { //是否接收到红外遥控信号
    IR_val = results.value;
    Serial.println(IR_val, HEX); //串口打印数据
    switch (IR_val) {
      case 0xFF629D:
        advance();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_front2);   //点阵显示前进图案
        break;

      case 0xFFA857:
        back();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_back2);   //点阵显示后退图案
        break;

      case 0xFF22DD:
        turnL();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_left2);    //点阵显示向左图案
        break;

      case 0xFFC23D:
        turnR();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_right2);   //显示右转图案
        break;

      case 0xFF02FD:
        stopp();
        myMatrix.clear();
        myMatrix.write();
        matrix_display(matrix_stop2);  //点阵显示停止图案
        break;

      default: break;
    }
    irrecv.resume();// 接收下个数据
  }

}

void advance() { //小车前进
  digitalWrite(MA, LOW); //电机A正转
  analogWrite(PWMA, speeds); //电机A速度为speeds
  digitalWrite(MB, LOW); //电机B正转
  analogWrite(PWMB, speeds); //电机B速度为speeds
}

void back() { //小车后退
  digitalWrite(MA, HIGH); //电机A反转
  analogWrite(PWMA, speeds); //电机A速度为speeds
  digitalWrite(MB, HIGH); //电机B反转
  analogWrite(PWMB, speeds); //电机B速度为speeds
}

void turnL() { //小车左旋转
  digitalWrite(MA, HIGH); //电机A反转
  analogWrite(PWMA, speeds); //电机A速度为speeds
  digitalWrite(MB, LOW); //电机B正转
  analogWrite(PWMB, speeds); //电机B速度为speeds
}

void turnR() { //小车右旋转
  digitalWrite(MA, LOW); //电机A正转
  analogWrite(PWMA, speeds); //电机A速度为speeds
  digitalWrite(MB, HIGH); //电机B反转
  analogWrite(PWMB, speeds); //电机B速度为speeds
}
void stopp() { //小车停止
  analogWrite(PWMA, 0); //电机A速度为0
  analogWrite(PWMB, 0); //电机B速度为0
}

void speeds_a() { //增速函数
  int a_flag = 1; //用于while循环
  while (a_flag) {
    Serial.println(speeds);  //显示速度
    if (speeds < 255) { //最大增到255
      speeds++;
      delay(10);  //调节增速的速度
    }
    blue_val = Serial.read();
    if (blue_val == 'S')a_flag = 0; //接收到‘S’停止加速
  }
}

void speeds_d() { //减速函数
  int d_flag = 1; //用于while循环
  while (d_flag) {
    Serial.println(speeds);  //显示速度
    if (speeds > 0) { //最小减到0
      speeds--;
      delay(10);    //调节减速的速度
    }
    blue_val = Serial.read();
    if (blue_val == 'S')d_flag = 0; //接收到‘S’停止减速
  }
}

void follow() {
  int follow_flag = 1;
  while (follow_flag) {
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
    blue_val = Serial.read();
    if (blue_val == 'S') { //接收到‘S’退出循环，小车停止
      follow_flag = 0;
      stopp();
    }
  }
}

void avoid() {
  int avoid_flag = 1;
  while (avoid_flag) {
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
    blue_val = Serial.read();
    if (blue_val == 'S') { //接收到‘S’退出循环，小车停止
      avoid_flag = 0;
      stopp();
    }
  }
}

void track() {
  int track_flag = 1;
  while (track_flag) {
    L_val = digitalRead(L_pin); //读取左边传感器的值
    M_val = digitalRead(M_pin); //读中间传感器的值
    R_val = digitalRead(R_pin); //读取右边传感器的值
    if (M_val == 1) { //中间检测到黑线
      if (L_val == 1 && R_val == 0) { //如果左边检测到黑线，右边没有，左转
        turnL();
      }
      else if (L_val == 0 && R_val == 1) { //否则如果右边检测到黑线，左边没有，右转
        turnR();
      }
      else { //否则前进
        advance();
      }
    }
    else { //中间没检测到黑线
      if (L_val == 1 && R_val == 0) { //如果左边检测到黑线，右边没有，左转
        turnL();
      }
      else if (L_val == 0 && R_val == 1) { //否则如果右边检测到黑线，左边没有，右转
        turnR();
      }
      else { //否则停止
        stopp();
      }
    }
    blue_val = Serial.read();
    if (blue_val == 'S') { //接收到‘S’退出循环，小车停止
      track_flag = 0;
      stopp();
    }
  }
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

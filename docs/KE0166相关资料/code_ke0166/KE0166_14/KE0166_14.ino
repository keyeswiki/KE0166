/*
  keyes smart turtle robot
  lesson 14
  Remote Control Turtle
  http://www.keyes-robot.com
*/
#include <Matrix.h>
#include <IRremote.h>
int RECV_PIN = A1; //定义IO口A1
IRrecv irrecv(RECV_PIN);
decode_results results;//声明一个IRremote库函数独有的变量类型
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
int IR_val;
int MA = 2; //定义电机A方向控制引脚为D2
int PWMA = 6; //定义电机A速度控制引脚为D6
int MB = 4; //定义电机A方向控制引脚为D4
int PWMB = 5; //定义电机A速度控制引脚为D5


void setup() {
  Serial.begin(9600);  //设置波特率为9600
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
  delay(500);
}
void loop() {
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

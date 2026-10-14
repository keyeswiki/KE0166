/*
  keyes smart turtle robot
  lesson 11
  Thacking turtle
  http://www.keyes-robot.com
*/
int L_pin = 11; //定义左边传感器引脚为D11
int M_pin = 7; //定义中间传感器引脚为D7
int R_pin = 8; //定义右边传感器引脚为D8
int MA = 2; //定义电机A方向控制引脚为D2
int PWMA = 6; //定义电机A速度控制引脚为D6
int MB = 4; //定义电机A方向控制引脚为D4
int PWMB = 5; //定义电机A速度控制引脚为D5
int L_val, M_val, R_val;

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
void setup() {
  Serial.begin(9600); //设置波特率为9600
  pinMode(L_pin, INPUT); //循迹传感器引脚都配置为输入模式
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);
  pinMode(MA, OUTPUT); //配置电机引脚为输出模式
  pinMode(PWMA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(PWMB, OUTPUT);
}
void loop() {
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
}

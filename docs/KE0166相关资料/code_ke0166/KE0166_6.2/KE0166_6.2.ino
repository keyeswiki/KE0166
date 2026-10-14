/*
  keyes smart turtle robot
  lesson 6.2
  IRremote
  http://www.keyes-robot.com
*/
#include <IRremote.h>
int RECV_PIN = A1;//定义红外接收器的引脚为A1
int LED_PIN = 9; //定义发光LED引脚数字9
int a = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 初始化红外接收器
  pinMode(LED_PIN, OUTPUT); //设置发光LED引脚数字4
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF02FD & a == 0) //由上面的键值码，我们用的遥控器上的OK键，如果按下OK键
    {
      digitalWrite(LED_PIN, HIGH); //LED点亮
      a = 1;
    }
    else if (results.value == 0xFF02FD & a == 1) //再按一下
    {
      digitalWrite(LED_PIN, LOW); //LED熄灭
      a = 0;
    }
    irrecv.resume(); // 接收下一个值
  }
}

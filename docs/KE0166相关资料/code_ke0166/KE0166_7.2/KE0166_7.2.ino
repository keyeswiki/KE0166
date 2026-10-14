/*
  keyes smart turtle robot
  lesson 7.2
  bluetooth
  http://www.keyes-robot.com
*/
int ledpin = 9;
void setup()
{
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}
void loop()
{
  int i;
  if (Serial.available())
  {
    i = Serial.read();
    Serial.println("DATA RECEIVED:");
    if (i == 'B')
    {
      digitalWrite(ledpin, HIGH);
      Serial.println("led on");
    }
    if (i == 'S')
    {
      digitalWrite(ledpin, LOW);
      Serial.println("led off");
    }
  }
}

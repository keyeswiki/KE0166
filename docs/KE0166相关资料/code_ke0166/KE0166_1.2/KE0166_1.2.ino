/*
  keyes smart turtle robot
  lesson 1.2
  Blink
  http://www.keyes-robot.com
*/
void setup() {  // initialize digital pin 9 as an output.
  pinMode(9, OUTPUT);
}
// the loop function runs over and over again forever
void loop()
{
  digitalWrite(9, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100); // wait for 0.1 second
  digitalWrite(9, LOW); // turn the LED off by making the voltage LOW
  delay(100); // wait for 0.1 second
}

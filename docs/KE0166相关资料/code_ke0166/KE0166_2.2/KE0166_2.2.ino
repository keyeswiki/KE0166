/*
  keyes smart turtle robot
  lesson 2.2
  PWM
  http://www.keyes-robot.com
*/
int ledPin = 9; // Define the LED pin at D9
void setup () {
  pinMode (ledPin, OUTPUT); // initialize ledpin as an output.
}
void loop () {
  for (int brightness = 0; brightness < 255; brightness = brightness + 1) {
    analogWrite (ledPin, brightness); // LED lights gradually light up
    delay (30); // delay 30ms
  }
  for (int brightness = 255; brightness > 0; brightness = brightness - 1) {
    analogWrite (ledPin, brightness); // LED gradually goes out
    delay (30); // delay 30ms
  }
}

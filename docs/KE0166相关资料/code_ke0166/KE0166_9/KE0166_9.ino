/*
  keyestudio smart turtle robot
  lesson 9
  Matrix
  http://www.keyestudio.com
*/
#include <Matrix.h>
Matrix myMatrix(A4, A5);
uint8_t LedArray1[8] = {0x42, 0xA5, 0x00, 0x00, 0x18, 0x42, 0x3C, 0x00};
uint8_t  LEDArray[8];
void setup() {
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
}

/*!
 * @file readData.ino
 * @brief 这是一个获取麦克风数据并将数据打印出来
 * @copyright  Copyright (c) 2022 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-02-18
 * @url https://github.com/DFRobot/DFRobot_Microphone
 */

#include "DFrobot_Microphone.h"

#define SAMPLE_RATE     (44100)
#define I2S_BCK_IO      (25)
#define I2S_WS_IO       (16)
#define I2S_DI_IO       (27)
#define DATA_BIT        (16)
#define MODE_PIN        (4)
DFRobot_Microphone microphone(I2S_BCK_IO, I2S_WS_IO, I2S_DI_IO,MODE_PIN);
char i2sReadrawBuff[100];
void setup() {
  Serial.begin(115200);
  while(microphone.begin(SAMPLE_RATE, DATA_BIT, microphone.eLiftChannel) != 0){
      Serial.println(" I2S init failed");
  }
  Serial.println("I2S init success");
  
}

void loop() {
  microphone.read(i2sReadrawBuff,100);
//  Serial.print("right channel=");
//  Serial.println((int16_t)(i2sReadrawBuff[0]|i2sReadrawBuff[1]<<8));
  Serial.print("left channel=");
  Serial.println((int16_t)(i2sReadrawBuff[2]|i2sReadrawBuff[3]<<8));
  delay(100);
}

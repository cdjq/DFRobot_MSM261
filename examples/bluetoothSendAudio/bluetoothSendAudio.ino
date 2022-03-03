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
#include "DFRobot_BluetoothA2DPSource.h"


#define SAMPLE_RATE     (44100)
#define I2S_BCK_IO      (25)
#define I2S_WS_IO       (16)
#define I2S_DI_IO       (27)
#define DATA_BIT        (16)
#define MODE_PIN        (4)

DFRobot_Microphone microphone(I2S_BCK_IO, I2S_WS_IO, I2S_DI_IO,MODE_PIN);
DFRobot_BluetoothA2DPSource a2dp;
const char* bleName = "KFC";
char communicationData[512];

static int32_t btAppA2dDataCb(uint8_t *data, int32_t len)
{   
    if (len < 0 || data == NULL) {
        return 0;
    }
    microphone.read(communicationData, len);
    for (int i = 0; i < (len >> 1); i++) {
        data[(i << 1)] = communicationData[i<<1];
        data[(i << 1) + 1] = communicationData[(i<<1)+1];
    }
    return len;
}

void setup() {
  Serial.begin(115200);
  while(microphone.begin(SAMPLE_RATE, DATA_BIT, microphone.eRightChannel) != 0){
      Serial.println(" I2S init failed");
  }
  Serial.println("I2S init success");
  while(!a2dp.begin(bleName,btAppA2dDataCb,50)){
    Serial.println(" a2dp init failed");
  }
}

void loop() {
}

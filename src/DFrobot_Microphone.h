/*!
 * @file DFRobot_Microphone.h
 * @brief 这是麦克风库的方法实现
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2022-2-18
 * @url https://github.com/DFRobot/DFRobot_Microphone
 */
#ifndef _DFROBOT_MICROPHONE_H_
#define _DFROBOT_MICROPHONE_H_

#include "Arduino.h"
#include <driver/i2s.h>
#include "stdio.h"

#define I2S_NUM         (i2s_port_t)(0)

#define ENABLE_DBG //!< 打开这个宏, 可以看到程序的详细运行过程
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif
class DFRobot_Microphone
{
    
public:
    /**
     * @fn eMode
     * @brief 声道选择
     */
    typedef enum{
        eLiftChannel  = 0,
        eRightChannel = 1,
    }eMode;
    /**
     * @brief 麦克风构造函数
     * @param bckIoNum 时钟引脚配置
     * @param wsIoNum  ws引脚配置
     * @param dInNum   数据获取引脚
     * @param modePin  模式配置引脚
     */
    DFRobot_Microphone(uint8_t bckIoNum, uint8_t wsIoNum, uint8_t dInNum, uint8_t modePin);
    /**
     * @fn begin
     * @brief 初始化设备
     * @param baudRate 通信速率
     * @param bit 数据位数
     * @return 返回初始化状态
     */
    uint8_t begin(uint16_t baudRate,uint8_t bit,eMode mode);

    /**
     * @brief 获取麦克风返回数据
     * @param buffer 获取数据得buffer
     * @param len    获取数据长度
     * @return 返回获取数据长度
     */
    uint32_t read(char *buffer,size_t len);

    /**
     * @brief 构建WAVE文件的头
     * @param header 构建WAVE的文件
     * @param totalDataLen 需要写入的数据长度
     * @param longSampleRate 采样频率
     * @param channels 声道数量
     * @param byteRate 字节速率 计算方式：采样速率x声道数量x数据位数/8
     * @param blockAlign 块对齐方式 计算方式：声道数量x数据位数/8
     */
    void createWavHeader(byte* header, int totalDataLen, int longSampleRate, uint8_t channels, int byteRate, uint8_t blockAlign);
   
private:
    uint8_t _bckIoNum;
    uint8_t _wsIoNum;
    uint8_t _dInNum;
    uint8_t _modePin;
    uint8_t _mode;

};
#endif
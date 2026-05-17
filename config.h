#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <reg51.h>

// 数据类型定义
typedef unsigned char uchar;
typedef unsigned int uint;

// 硬件引脚定义
#define DS18B20_PORT P1_6      // DS18B20数据端口
sbit DQ = P1^6;                 // DS18B20数据线

#define FAN_PWM_PORT P1_0      // PWM风扇控制端口
sbit FAN_PWM = P1^0;            // PWM控制脚

#define LED_PORT P1_1          // LED指示灯
sbit LED = P1^1;

// 按键定义
sbit KEY1 = P3^0;              // 增档按键
sbit KEY2 = P3^1;              // 减档按键
sbit KEY3 = P3^2;              // 自动/手动切换
sbit KEY4 = P3^3;              // 定时按键

// LCD1602接口
#define LCD_DB P0              // 数据口
sbit LCD_RS = P3^4;            // 片选
sbit LCD_RW = P3^5;            // 读写
sbit LCD_EN = P3^6;            // 使能

// 系统参数配置
#define TEMP_HIGH 28           // 高温触发值
#define TEMP_LOW  25           // 低温关闭值
#define TEMP_ALARM 35          // 报警温度值

#define FAN_OFF 0              // 风扇关闭
#define FAN_LEVEL1 25          // 1档-25%
#define FAN_LEVEL2 50          // 2档-50%
#define FAN_LEVEL3 75          // 3档-75%
#define FAN_LEVEL4 90          // 4档-90%
#define FAN_LEVEL5 100         // 5档-100%

// 系统频率
#define FOSC 12000000L         // 晶振频率12MHz

#endif

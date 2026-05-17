/*
 * system.h - 系统头文件
 * 
 * STC89C51 智能温控风扇系统
 * 定义全局变量、数据类型和函数声明
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "config.h"
#include <intrins.h>

/* ==================== 寄存器定义 ==================== */
sfr P0 = 0x80;          // P0口
sfr P1 = 0x90;          // P1口
sfr P2 = 0xa0;          // P2口
sfr P3 = 0xb0;          // P3口

sfr SP = 0x81;          // 栈指针
sfr TMOD = 0x89;        // 定时器模式
sfr TL0 = 0x8a;         // 定时器0低字节
sfr TH0 = 0x8b;         // 定时器0高字节
sfr TL1 = 0x8c;         // 定时器1低字节
sfr TH1 = 0x8d;         // 定时器1高字节
sfr TCON = 0x88;        // 定时器控制
sfr TR0 = TCON^3;       // 定时器0运行控制位
sfr TF0 = TCON^5;       // 定时器0溢出标志
sfr TR1 = TCON^6;       // 定时器1运行控制位
sfr TF1 = TCON^7;       // 定时器1溢出标志

sfr IE = 0xa8;          // 中断使能
sfr ET0 = IE^3;         // 定时器0中断使能
sfr EA = IE^7;          // 全局中断使能

sfr IP = 0xb8;          // 中断优先级

/* ==================== 全局变量声明 ==================== */
extern u16 system_ticks;        // 系统滴答计数
extern u8  current_mode;        // 当前工作模式
extern u16 current_temp;        // 当前温度 (0.1°C为单位)
extern u16 target_temp;         // 目标温度
extern u8  pwm_duty;            // PWM占空比 (0-100)

/* ==================== 系统函数声明 ==================== */

/**
 * 系统初始化
 * 初始化定时器、IO、中断
 */
void system_init(void);

/**
 * 延时函数 - 毫秒
 */
void delay_ms(u16 ms);

/**
 * 延时函数 - 微秒
 * 用于DS18B20时序控制
 */
void delay_us(u16 us);

/**
 * 获取系统运行时间 (毫秒)
 */
u32 get_system_ms(void);

/**
 * 重置系统滴答计数器
 */
void reset_ticks(void);

/**
 * 定时器0中断处理
 * 中断周期: 1ms
 */
void timer0_isr(void) interrupt 1;

/* ==================== 数据类型定义 ==================== */
typedef unsigned char   u8;
typedef signed char     s8;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned long   u32;
typedef signed long     s32;

#endif /* __SYSTEM_H__ */

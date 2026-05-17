#include "config.h"
#include "delay.h"
#include "ds18b20.h"
#include "pwm.h"
#include "lcd1602.h"
#include "key.h"

// 系统变量
static uchar fan_level = 0;           // 当前风扇档位
static uchar auto_mode = 1;           // 自动模式标志（1为自动，0为手动）nstatic uchar timer_count = 0;         // 定时计数器
static uchar timer_enable = 0;        // 定时使能标志
static uint timer_value = 0;          // 定时剩余时间（秒）
static uchar alarm_flag = 0;          // 报警标志

/*
 * 系统初始化
 */
void system_init(void) {
    delay_ms(100);
    ds18b20_init();
    pwm_init();
    lcd_init();
    key_init();
    
    // 初始显示
    lcd_display_string(0, 0, "Temp:");
    lcd_display_string(1, 0, "Level:0");
    lcd_display_string(1, 8, "Auto");
}

/*
 * 自动温控处理
 */
void auto_control(float temp) {
    if(auto_mode) {
        if(temp >= TEMP_ALARM) {
            // 超过报警温度，最高档运行
            fan_level = 5;
            alarm_flag = 1;
            LED = 1;  // 点亮报警指示灯
        } else if(temp >= TEMP_HIGH) {
            // 高于触发温度
            if(fan_level < 5) {
                fan_level = (temp - TEMP_HIGH + 2) / 1 + 1;  // 根据温度调节
                if(fan_level > 5) fan_level = 5;
            }
            alarm_flag = 0;
            LED = 0;
        } else if(temp < TEMP_LOW) {
            // 低于关闭温度
            fan_level = 0;
            alarm_flag = 0;
            LED = 0;
        }
    }
}

/*
 * 按键处理
 */
void handle_key(uchar key_val) {
    switch(key_val) {
        case KEY1_PRESS:
            // 增档
            if(!auto_mode) {
                if(fan_level < 5) {
                    fan_level++;
                    fan_set_level(fan_level);
                }
            }
            break;
            
        case KEY2_PRESS:
            // 减档
            if(!auto_mode) {
                if(fan_level > 0) {
                    fan_level--;
                    fan_set_level(fan_level);
                }
            }
            break;
            
        case KEY3_PRESS:
            // 切换自动/手动模式
            auto_mode = !auto_mode;
            if(!auto_mode) {
                fan_level = 0;  // 手动模式初始化为关闭
                fan_set_level(0);
            }
            break;
            
        case KEY4_PRESS:
            // 定时功能
            if(timer_enable) {
                timer_enable = 0;  // 关闭定时
                timer_value = 0;
            } else {
                timer_enable = 1;  // 启动定时
                timer_value = 600; // 10分钟
            }
            break;
    }
}

/*
 * 定时处理
 */
void timer_process(void) {
    timer_count++;
    if(timer_count >= 100) {  // 每秒执行一次
        timer_count = 0;
        if(timer_enable && timer_value > 0) {
            timer_value--;
            if(timer_value == 0) {
                timer_enable = 0;  // 时间到，关闭定时
                fan_level = 0;
                fan_set_level(0);
            }
        }
    }
}

/*
 * LCD显示更新
 */
void display_update(float temp) {
    // 显示温度
    lcd_set_pos(0, 6);
    lcd_display_float(0, 6, temp);
    lcd_display_char(0, 11, 'C');
    
    // 显示风扇档位
    lcd_set_pos(1, 7);
    lcd_display_char(1, 7, fan_level + '0');
    
    // 显示模式
    if(auto_mode) {
        lcd_display_string(1, 9, "Auto ");
    } else {
        lcd_display_string(1, 9, "Hand ");
    }
    
    // 显示报警状态
    if(alarm_flag) {
        lcd_display_char(0, 15, '*');
    }
}

/*
 * 主程序
 */
void main(void) {
    float temperature = 0;
    uchar key_val = 0;
    static uchar temp_count = 0;
    
    system_init();
    
    // 启动温度转换
    ds18b20_start_convert();
    
    while(1) {
        // 按键扫描
        key_val = key_scan();
        if(key_val != KEY_NONE) {
            handle_key(key_val);
        }
        
        // 每500ms读取一次温度
        temp_count++;
        if(temp_count >= 50) {
            temp_count = 0;
            temperature = ds18b20_read_temp();
            
            // 自动控制
            auto_control(temperature);
            
            // 设置风扇
            fan_set_level(fan_level);
            
            // 显示更新
            display_update(temperature);
            
            // 启动下一次温度转换
            ds18b20_start_convert();
        }
        
        // 定时处理
        timer_process();
        
        delay_ms(10);
    }
}

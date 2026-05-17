#include "pwm.h"

/*
 * PWM初始化
 * 使用定时器0产生PWM波
 */
void pwm_init(void) {
    TMOD |= 0x01;     // 定时器0工作在模式1（16位计数器）
    TH0 = 0xFC;       // 重载值
    TL0 = 0x18;
    TR0 = 1;          // 启动定时器0
    ET0 = 1;          // 使能定时器0中断
    EA = 1;           // 使能全局中断
}

/*
 * 设置PWM占空比
 * duty: 占空比（0-100）
 */
void pwm_set_duty(uchar duty) {
    if(duty == 0) {
        FAN_PWM = 0;
    } else if(duty >= 100) {
        FAN_PWM = 1;
    } else {
        // PWM产生逻辑在定时器中断中实现
        // 这里只是设置占空比参数
    }
}

/*
 * 设置风扇档位（0-5档）
 * level: 风扇档位
 */
void fan_set_level(uchar level) {
    switch(level) {
        case 0:
            pwm_set_duty(0);     // 关闭
            break;
        case 1:
            pwm_set_duty(FAN_LEVEL1);
            break;
        case 2:
            pwm_set_duty(FAN_LEVEL2);
            break;
        case 3:
            pwm_set_duty(FAN_LEVEL3);
            break;
        case 4:
            pwm_set_duty(FAN_LEVEL4);
            break;
        case 5:
            pwm_set_duty(FAN_LEVEL5);
            break;
        default:
            pwm_set_duty(0);
    }
}

/*
 * 风扇关闭
 */
void fan_off(void) {
    FAN_PWM = 0;
}

/*
 * 风扇开启
 */
void fan_on(uchar level) {
    fan_set_level(level);
}

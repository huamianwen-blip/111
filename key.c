#include "key.h"
#include "delay.h"

/*
 * 按键初始化
 */
void key_init(void) {
    // 按键已由config.h定义，这里为扩展功能预留
}

/*
 * 按键扫描
 * 返回值：按下的按键值（1-4）或0（无按键）
 */
uchar key_scan(void) {
    static uchar key_lock = 0;  // 按键锁
    
    if(key_lock) {
        if(KEY1 && KEY2 && KEY3 && KEY4) {
            key_lock = 0;  // 解除锁定
        }
        return KEY_NONE;
    }
    
    // 扫描KEY1
    if(!KEY1) {
        delay_ms(20);  // 去抖
        if(!KEY1) {
            key_lock = 1;
            return KEY1_PRESS;
        }
    }
    
    // 扫描KEY2
    if(!KEY2) {
        delay_ms(20);
        if(!KEY2) {
            key_lock = 1;
            return KEY2_PRESS;
        }
    }
    
    // 扫描KEY3
    if(!KEY3) {
        delay_ms(20);
        if(!KEY3) {
            key_lock = 1;
            return KEY3_PRESS;
        }
    }
    
    // 扫描KEY4
    if(!KEY4) {
        delay_ms(20);
        if(!KEY4) {
            key_lock = 1;
            return KEY4_PRESS;
        }
    }
    
    return KEY_NONE;
}

/*
 * 按键处理（在main函数中调用）
 */
void key_process(uchar key_val) {
    // 按键处理逻辑在main.c中实现
}

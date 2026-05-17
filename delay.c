#include "delay.h"

/*
 * 毫秒级延时
 * ms: 延时毫秒数
 */
void delay_ms(uint ms) {
    uchar i, j;
    while(ms--)
        for(i=0; i<123; i++)
            for(j=0; j<1; j++);
}

/*
 * 微秒级延时
 * us: 延时微秒数
 */
void delay_us(uint us) {
    uchar i;
    while(us--)
        for(i=0; i<10; i++);
}

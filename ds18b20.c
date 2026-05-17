#include "ds18b20.h"
#include "delay.h"

/*
 * DS18B20初始化
 */
void ds18b20_init(void) {
    DQ = 0;
    delay_us(30);
    DQ = 1;
    delay_us(30);
}

/*
 * DS18B20复位
 * 返回值：1表示存在，0表示不存在
 */
uchar ds18b20_reset(void) {
    uchar i = 0;
    
    DQ = 0;
    delay_us(480);
    DQ = 1;
    delay_us(70);
    
    i = DQ;
    delay_us(410);
    
    return i;
}

/*
 * 向DS18B20写入一个字节
 */
void ds18b20_write_byte(uchar dat) {
    uchar i, j;
    
    for(j = 0; j < 8; j++) {
        DQ = 0;
        delay_us(5);
        
        if(dat & 0x01) {
            DQ = 1;
        }
        
        delay_us(60);
        DQ = 1;
        delay_us(5);
        dat >>= 1;
    }
}

/*
 * 从DS18B20读取一个字节
 */
uchar ds18b20_read_byte(void) {
    uchar i, j = 0;
    
    for(i = 0; i < 8; i++) {
        DQ = 0;
        delay_us(3);
        DQ = 1;
        delay_us(10);
        
        if(DQ) {
            j |= 0x80;
        }
        
        delay_us(50);
        j >>= 1;
    }
    
    return j;
}

/*
 * 启动DS18B20进行温度转换
 */
void ds18b20_start_convert(void) {
    ds18b20_reset();
    delay_ms(1);
    ds18b20_write_byte(SKIP_ROM);
    delay_ms(1);
    ds18b20_write_byte(CONVERT_T);
    delay_ms(1);
}

/*
 * 读取DS18B20温度值
 * 返回值：温度值（浮点数）
 */
float ds18b20_read_temp(void) {
    uchar LSB, MSB;
    float temp;
    
    ds18b20_reset();
    delay_ms(1);
    ds18b20_write_byte(SKIP_ROM);
    delay_ms(1);
    ds18b20_write_byte(READ_SCRATCHPAD);
    delay_ms(1);
    
    LSB = ds18b20_read_byte();
    MSB = ds18b20_read_byte();
    
    // 温度计算（12位分辨率）
    temp = (MSB << 8 | LSB) * 0.0625;
    
    return temp;
}

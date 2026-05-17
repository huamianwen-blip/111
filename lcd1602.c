#include "lcd1602.h"
#include "delay.h"

/*
 * LCD1602初始化
 */
void lcd_init(void) {
    delay_ms(15);
    
    lcd_write_cmd(0x38);  // 8位数据，2行显示，5x8点阵
    delay_ms(5);
    lcd_write_cmd(0x38);
    delay_ms(5);
    lcd_write_cmd(0x38);
    delay_ms(5);
    
    lcd_write_cmd(0x08);  // 显示关闭
    delay_ms(5);
    lcd_write_cmd(0x01);  // 清屏
    delay_ms(5);
    lcd_write_cmd(0x06);  // 写入新数据时地址自增
    delay_ms(5);
    lcd_write_cmd(0x0C);  // 显示开启，光标关闭
    delay_ms(5);
}

/*
 * LCD写入命令
 */
void lcd_write_cmd(uchar cmd) {
    LCD_DB = cmd;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 1;
    delay_us(30);
    LCD_EN = 0;
    delay_ms(1);
}

/*
 * LCD写入数据
 */
void lcd_write_dat(uchar dat) {
    LCD_DB = dat;
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 1;
    delay_us(30);
    LCD_EN = 0;
    delay_ms(1);
}

/*
 * 设置LCD显示位置
 * row: 行（0或1）
 * col: 列（0-15）
 */
void lcd_set_pos(uchar row, uchar col) {
    uchar addr;
    
    if(row == 0) {
        addr = 0x80 + col;
    } else {
        addr = 0xC0 + col;
    }
    
    lcd_write_cmd(addr);
}

/*
 * LCD显示字符串
 */
void lcd_display_string(uchar row, uchar col, uchar *str) {
    lcd_set_pos(row, col);
    
    while(*str) {
        lcd_write_dat(*str++);
    }
}

/*
 * LCD显示单个字符
 */
void lcd_display_char(uchar row, uchar col, uchar chr) {
    lcd_set_pos(row, col);
    lcd_write_dat(chr);
}

/*
 * LCD显示整数
 */
void lcd_display_number(uchar row, uchar col, uint num) {
    uchar str[6], i = 0;
    
    if(num == 0) {
        lcd_display_char(row, col, '0');
        return;
    }
    
    while(num) {
        str[i++] = num % 10 + '0';
        num /= 10;
    }
    
    lcd_set_pos(row, col + i - 1);
    
    while(i--) {
        lcd_write_dat(str[i]);
    }
}

/*
 * LCD显示浮点数
 */
void lcd_display_float(uchar row, uchar col, float num) {
    uint int_part = (uint)num;
    uchar dec_part = (uchar)((num - int_part) * 100);
    
    lcd_set_pos(row, col);
    
    // 显示整数部分
    if(int_part >= 10) {
        lcd_write_dat(int_part / 10 + '0');
        lcd_write_dat(int_part % 10 + '0');
    } else {
        lcd_write_dat(' ');
        lcd_write_dat(int_part + '0');
    }
    
    lcd_write_dat('.');
    
    // 显示小数部分
    lcd_write_dat(dec_part / 10 + '0');
    lcd_write_dat(dec_part % 10 + '0');
}

/*
 * LCD清屏
 */
void lcd_clear(void) {
    lcd_write_cmd(0x01);
    delay_ms(10);
}

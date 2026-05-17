#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "config.h"

void lcd_init(void);
void lcd_write_cmd(uchar cmd);
void lcd_write_dat(uchar dat);
void lcd_set_pos(uchar row, uchar col);
void lcd_display_string(uchar row, uchar col, uchar *str);
void lcd_display_char(uchar row, uchar col, uchar chr);
void lcd_display_number(uchar row, uchar col, uint num);
void lcd_display_float(uchar row, uchar col, float num);
void lcd_clear(void);

#endif

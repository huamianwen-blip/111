#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "config.h"

// DS18B20 ROM命令
#define SKIP_ROM 0xCC
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SEARCH_ROM 0xF0

// DS18B20功能命令
#define WRITE_SCRATCHPAD 0x4E
#define READ_SCRATCHPAD 0xBE
#define COPY_SCRATCHPAD 0x48
#define CONVERT_T 0x44
#define RECALL_EE 0xB8
#define READ_POWER_SUPPLY 0xB4

void ds18b20_init(void);
uchar ds18b20_reset(void);
void ds18b20_write_byte(uchar dat);
uchar ds18b20_read_byte(void);
void ds18b20_start_convert(void);
float ds18b20_read_temp(void);

#endif

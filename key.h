#ifndef __KEY_H__
#define __KEY_H__

#include "config.h"

#define KEY_NONE 0
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4

void key_init(void);
uchar key_scan(void);
void key_process(uchar key_val);

#endif

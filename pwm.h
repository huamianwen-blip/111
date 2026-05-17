#ifndef __PWM_H__
#define __PWM_H__

#include "config.h"

void pwm_init(void);
void pwm_set_duty(uchar duty);  // 0-100
void fan_set_level(uchar level); // 0-5档
void fan_off(void);
void fan_on(uchar level);

#endif

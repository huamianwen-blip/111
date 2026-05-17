# PWM风扇调速控制原理

## PWM基本概念
PWM(Pulse Width Modulation)脉宽调制是通过改变方波的占空比来改变平均电压，从而实现电机转速调节。

## 占空比与风扇档位对应关系
```
档位 | 占空比 | 运行状态
-----|--------|--------
0    | 0%     | 停止
1    | 25%    | 低速
2    | 50%    | 中低速
3    | 75%    | 中高速
4    | 90%    | 高速
5    | 100%   | 全速
```

## 实现方法
### 方案1：硬件PWM（推荐）
使用单片机定时器生成PWM波
- 周期: 20ms (50Hz)
- 分辨率: 100级

### 方案2：软件PWM
在中断中切换GPIO电平

## 代码实现
```c
void pwm_set_duty(uchar duty) {
    if(duty == 0) {
        FAN_PWM = 0;      // 停止
    } else if(duty >= 100) {
        FAN_PWM = 1;      // 全速
    } else {
        // PWM产生
    }
}

void fan_set_level(uchar level) {
    uchar duty_table[] = {0, 25, 50, 75, 90, 100};
    pwm_set_duty(duty_table[level]);
}
```

## 驱动电路
```
P1.0 ----[1K]----| MOSFET Gate
                  |
                  |/
                  |---- 风扇正极
                  |\\
                  |
               GND

风扇负极 ---- GND
```

## 注意事项
1. 风扇电源需要单独供电（建议5V/1A以上）
2. 使用MOS管隔离单片机和风扇电路
3. 加反向二极管防止反电动势
4. PWM频率建议在10kHz以上（减少噪音）

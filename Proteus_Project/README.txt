# Proteus仿真文件说明

本文件夹用于存放Proteus仿真文件

## 使用步骤
1. 使用Proteus 8.17及以上版本打开.dsn文件
2. 编译main.c等源文件生成hex文件
3. 在Proteus中配置单片机hex文件路径
4. 运行仿真

## 硬件连接
- P1.6: DS18B20数据线
- P1.0: PWM风扇控制
- P1.1: LED指示灯
- P3.0-P3.3: 按键输入
- P0: LCD数据线
- P3.4-P3.6: LCD控制线

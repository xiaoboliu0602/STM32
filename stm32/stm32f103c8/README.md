# STM32 外设相关驱动代码

`STM32F10x_StdPeriph_Lib_V3.5.0`

```sh
usart1                    # 串口驱动，发送和接收；

gpio                      # IO 口驱动；

led                       # LED 驱动测试；

clk_config                # 系统时钟配置；

key                       # 按键配置；

delay                     # 滴答延时配置及程序；

ds18b20                   # 温度传感器 DS18B20 驱动；

ds1302                    # 万年历时钟芯片 DS1302 驱动；

time_cyccnt               # 内核心跳计数器，时间更精准；

timing_systick            # 滴答计时器，提供一个有限范围增加的时钟，可以测量程序段运行时间； 

time2                     # 通用定时器 TIM2 驱动；

timer                     # 通用定时器 TIM2 驱动，有详细测试说明；
	
oled                      # SSD1306 0.69 ince OLED 屏驱动；

HC595                     # 三八译码器 74HC595 驱动；

bsp_GeneralTim            # PWM 配置；

exti_Config               # 外部中断配置；

Programming_moduleblock   # 矩阵键盘驱动；
```
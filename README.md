# [CH554](https://github.com/SoCXin/CH554)

[![sites](http://182.61.61.133/link/resources/SoC.png)](http://www.SoC.Xin)

[![Build Status](https://github.com/SoCXin/CH554/workflows/CI/badge.svg)](https://github.com/SoCXin/CH554/actions/workflows/CI.yml)

* [WCH](http://www.wch.cn/): [8051](https://github.com/SoCXin/8051)
* [L1R1](https://github.com/SoCXin/Level): 16/24 MHz

### [简介](https://github.com/SoCXin/CH554/wiki)

[CH554](https://github.com/SoCXin/CH554) 增强型E8051内核，79%指令是单字节单周期指令，2KB Boot + 14KB Flash，1K xRAM(支持DMA) +256B iRAM，128B DataFlash。

CH554提供丰富的接口资源，包括ADC模数转换、3组定时器和信号捕捉及PWM、双异步串口、SPI等。6通道电容检测模块，互电容方式支持最多15个触摸按键。内嵌全速USB控制器,支持USB HOST主机模式和USB DEVICE设备模式。

[![sites](docs/CH554.png)](http://www.wch.cn/products/CH554.html)

#### 关键特性

* USB 2.0 FS (H or D)
* 5V->3.3V LDO
* 128B DataFlash
* USB Type-C 主从检测
* 内置2KB BootLoader，支持USB和串口ISP

### [资源收录](https://github.com/SoCXin)

* [参考资源](src/)
* [参考文档](docs/)
* [参考工程](project/)

### [选型建议](https://github.com/SoCXin)

[CH554](https://github.com/SoCXin/CH554)是一款广泛应用的低成本USB HOST MCU，降配版本[CH552](https://github.com/SoCXin/CH552)具有更高性价比，应用于各种简单USB通信外设，已经积累了不少的开源的项目，尤其是在开源硬件领域，用于在板调试。

* [CH552](http://www.wch.cn/products/CH552.html)不支持USB-HOST主机模式
* [CH551](http://www.wch.cn/products/CH551.html)ROM降为10K，xRAM为512字节，串口仅UART0，封装仅SOP16，去掉了ADC和USB type-C功能。

* 各种小封装可选：TSSOP20/SOP16/QFN16/MSOP10

#### 相关开发板

[![sites](docs/B.png)](https://item.taobao.com/item.htm?spm=a230r.1.14.160.1b402171ANBDsc&id=598357002103&ns=1&abbucket=18#detail)

#### 完成度较高的开源项目

* [ch55xduino](https://github.com/DeqingSun/ch55xduino) 类arduino框架
* [ch554_sdcc](https://github.com/Blinkinlabs/ch554_sdcc) 基于SDCC的工程模板
* [ch55xtool](https://github.com/MarsTechHAN/ch552tool) 固件下载工具（python）


### [探索芯世界 www.SoC.xin](http://www.SoC.Xin)

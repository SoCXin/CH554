# [CH554](https://github.com/SoCXin/CH554)

[![sites](http://182.61.61.133/link/resources/SoC.png)](http://www.SoC.Xin)

[![Build Status](https://github.com/SoCXin/CH554/workflows/ubuntu/badge.svg)](https://github.com/SoCXin/CH554/actions/workflows/ubuntu.yml)

#### [Vendor](https://github.com/SoCXin/Vendor)：[WCH](http://www.wch.cn/)
#### [Core](https://github.com/SoCXin/8051)：[8051](https://github.com/SoCXin/8051)
#### [Level](https://github.com/SoCXin/Level)：24MHz

### [CH554简介](https://github.com/SoCXin/CH554/wiki)

[CH554](https://github.com/SoCXin/CH554) 增强型E8051内核，79%指令是单字节单周期指令，2KB Boot + 14KB Flash，1K xRAM(支持DMA) +256B iRAM，128B DataFlash。

CH554提供丰富的接口资源，包括ADC模数转换、3组定时器和信号捕捉及PWM、双异步串口、SPI等。6通道电容检测模块，互电容方式支持最多15个触摸按键。内嵌全速USB控制器,支持USB HOST主机模式和USB DEVICE设备模式。

[![sites](docs/CH554.png)](http://www.wch.cn/products/CH554.html)

#### 关键特性

* 集成 5V->3.3V LDO
* 128B DataFlash
* 内置24MHz时钟源和PLL
* 内置2KB BootLoader，支持USB和串口ISP
* Type-C主从检测
* USB全速主/从模式
* UART x 2 + SPI(M/S)
* 小封装(TSSOP20/SOP16/MSOP10/QFN16)

### [资源收录](https://github.com/SoCXin)

* [参考文档](docs/)
* [参考资源](src/)
* [参考工程](project/)

### [选型建议](https://github.com/SoCXin)

[CH554](https://github.com/SoCXin/CH554)是一款具备想象力的lowpin产品，在开源社区拥有不错的声望，该产品同族包括：

* [CH554](http://www.wch.cn/products/CH554.html) 包括4种封装型号(TSSOP20/SOP16/MSOP10/QFN16)
* [CH552](http://www.wch.cn/products/CH552.html) 不支持USB-HOST主机模式
* [CH551](http://www.wch.cn/products/CH551.html) 在CH552的基础上，ROM降为10K，片内xRAM为512字节，异步串口仅提供UART0，仅SOP16封装，去掉ADC和USB type-C功能。

###  [芯云 www.SoC.xin](http://www.SoC.Xin)

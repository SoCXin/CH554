
南京沁恒电子有限公司 2017.01
最新资料请到我们的网站上查询
http://wch.cn
http://winchiphead.com


文件目录
  |
  |-- README.TXT：目录文件说明
  |-- BRIEF
  |      |--CH554DS0.PDF：CH554简介
  |-- DS
  |      |--CH554DS1.PDF：CH554应用手册
  |-- EVT
  |      |-- EXAM: C例程
  |      |      |--CH554.uvproj：CH554 keil4工程文件
  |      |      |--Public
  |      |      |      |--CH554.H：CH554 C语言头文件，SFR定义
  |      |      |      |--CH554.INC：CH554汇编头文件，SFR定义
  |      |      |      |--Debug.C：UART0&1初始化、常用延时函数、UART0&1数据收发子函数,看门狗初始化
  |      |      |      |--Debug.H：UART0&1初始化、常用延时函数、UART0&1数据收发子函数、看门狗初始化声明
  |      |      |--ADC：
  |      |      |      |-- Main.C:ADC使用示例
  |      |      |      |-- ADC.C&H:ADC初始化，采样时钟设定，通道变化和电压比较功能函数定义
  |      |      |      |-- ADC.hex
  |      |      |--DataFlash
  |      |      |      |-- Main.C:DataFlash使用示例
  |      |      |      |-- DataFlash.C&H:DataFlash读写函数定义
  |      |      |      |-- DataFlash.hex
  |      |      |--GPIO
  |      |      |      |-- Main.C:GPIO使用示例
  |      |      |      |-- GPIO.C&H:GPIO设置函数定义
  |      |      |      |-- GPIO.hex
  |      |      |--IAP
  |      |      |      |--CH554IAPDemo.C IAP跳转BOOT升级参考文件
  |      |      |      |--CH554IAPDemo.hex
  |      |      |--PWM
  |      |      |      |-- Main.C:PWM使用示例
  |      |      |      |-- PWM.C&H:PWM初始化、设置函数定义
  |      |      |      |-- PWM.hex
  |      |      |--SPI
  |      |      |      |-- MainMaster.C:SPI主模式使用示例
  |      |      |      |-- MainSLV.C:SPI从模式使用示例
  |      |      |      |-- SPI.C&H:SPI主从设置和收发函数定义
  |      |      |      |-- MainMaster.hex
  |      |      |      |-- MainSLV.hex
  |      |      |--Timer
  |      |      |      |-- Main.C:Timer0&1&2定时，计数设置和捕捉功能使用示例
  |      |      |      |-- Timer.C&H:Timer0&1&2定时，计数设置和捕捉函数定义
  |      |      |      |-- Timer.hex  
  |      |      |--Type-C
  |      |      |      |-- Main.C:Type-C 主从模式使用示例
  |      |      |      |-- Type_C.C&H:Type-C主从模式配置函数定义
  |      |      |      |-- Type-C_DFP.hex 主模式 
  |      |      |      |-- Type-C_UFP.hex 从模式   
  |      |      |--TouchKey
  |      |      |      |-- Main.C:CH554 触摸按键中断和查询方式进行采集并报告当前采样通道按键状态，包含初始化和按键采样等演示函数  
  |      |      |      |-- TouchKey.C&H:TouchKey开启，通道切换和中断采集函数
  |      |      |      |-- TouchKey.hex
  |      |      |--Compare
  |      |      |      |-- Main.C:CH554 比较器示例，比较器使能，通道设置，中断/查询方式查询结果  
  |      |      |      |-- Compare.C&H:比较器使能，通道选择，中断函数
  |      |      |      |-- Compare.hex 
  |      |      |--UART1
  |      |      |      |-- Main.C:CH554 串口1查询、中断演示  
  |      |      |      |-- UART1.C&H:串口收发函数与初始化
  |      |      |      |-- UART1.hex 
  |      |      |--USB
  |      |      |      |-- Device
  |      |      |      |      |-- CompositeKM .C:模拟键鼠例程，支持部分类命令
  |      |      |      |      |-- CompositeKM.hex 
  |      |      |      |      |-- VendorDefinedDev.C:模拟厂商自定义设备，需要安装CH372驱动，可以通过372test.exe调试(批量数据收发)
  |      |      |      |      |-- VendorDefinedDev.hex
  |      |      |      |      |-- CompatibilityHID.C:模拟HID兼容设备，支持中断上下传
  |      |      |      |      |-- CompatibilityHID.hex  
  |      |      |      |-- Host
  |      |      |      |      |-- USBHostHUB_KM.C: USB主机应用例子,初始化和枚举USB端口连接的设备,支持一级外部HUB,可以操作USB键鼠和HUB，打印机,包含HID类命令处理
  |      |      |      |      |-- USBHostHUB_KM.hex: 
  |      |      |      |      |-- TOOL
  |      |      |      |           |-- UARTDemo.apk:AOA调试配套APK文件
  |      |      |      |-- U_DISK
  |      |      |      |      |-- EXAM1.C:C示例源程序,以字节为单位读写文件，包括文件创建、删除、修改文件属性,修改文件名
  |      |      |      |      |-- EXAM1.hex
  |      |      |      |      |-- EXAM11.C:C示例源程序,枚举根目录或者指定目下的文件
  |      |      |      |      |-- EXAM11.hex:
  |      |      |      |-- USB_LIB
  |      |      |      |      |-- CH554UFI.C:CH554 U盘读写文件系统库常用接口函数
  |      |      |      |      |-- CH554UFI.C:CH554 U盘读写文件系统库常用接口函数
  |      |      |      |      |-- CH554UFR.H:CH554 U盘只读文件系统库变量和函数声明头文件  
  |      |      |      |      |-- CH554UFR.H:CH554 U盘只读文件系统库变量和函数声明头文件
  |      |      |      |      |-- CH554UFR.LIB:CH554 U盘只读文件系统库文件(编译器内存模式设置成:small/large)  
  |      |      |      |      |-- CH554UFI.LIB:CH554 U盘文件系统库文件(编译器内存模式设置成:small)
  |      |      |      |      |-- CH554UFX.LIB:U盘文件系统库文件(编译器内存模式设置成:large)
  |      |      |      |      |-- USBHOST.C&H:CH554 USB主机控制传输函数定义
  |      |      |      |      |-- CH554UF_README.TXT:CH554 U盘文件系统变更文档
  |      |-- PUB: 评估板说明
  |      |      |-- CH554EVT.PDF: 评估板和EVT资料包说明
  |      |      |-- CH554SCH.PDF: 评估板原理图
  |      |      |-- CH55X指令周期.PDF

2017-7-5 14:29
1、修改BUG，增加CH55X指令周期.PDF。
2、增加CH55X只读文件系统库。

2017-11-21 16:07
1、修改Debug文件，方便系统主频定义。
2、修改GPIO文件，搭配新的EVT板演示。
3、修改TouchKey文件，搭配EVT板演示。
4、修改CompositeKM文件，支持端点0通过SET_Report和GET_Report收发数据。
5、修改CH554EVT.PDF文件，增加新评估版说明和ISP软件更新。
6、修改CH554SCH.PDF文件，增加新评估版说明。
7、删除PCB文件。

2018-2-28 10:19
1、修改SPI主从机文件，改为主机和从机进行数据交互。
2、修改USBHOST.C文件，在操作低速设备时，开启PRE。
3、修改PWM文件注释，明确PWM时钟。

2018-7-23 9:10
1、修改USBHOST.C文件，增加HubLowSpeed变量，用以解决操作HUB下低速设备的问题。
2、修改HOSTHostHUB_KM.C文件关于多设备操作部分程序结构以及复合HID设备操作端点过滤问题。
3、修改HOSTHostHUB_KM.C以及USBHOST.C文件，添加安卓AOA 1.0协议支持，以及该目录下添加APK文件。
4、修改CompatibilityHID.C文件关于USB数据上传的方式，采用标志位判断的方法。
5、添加UART1文件夹，提供查询中断等相关操作，Debug.C文件删除串口1操作代码
6、修改CH554EVT.PDF 关于器件库、EVT目录文件结构的说明。

2019-7-22 10:13
1、ADC：
修改ADC.C、ADC.H和Main.C文件，将4个通道ADC采样值打印出来，且采样值以十进制显示，提升用户体验；
2、SPI：
修改MainMaster.C文件，主机初始化完成后增加100ms延时，等待从机初始化完成；
3、TouchKey：
修改TouchKey.C、TouchKey.H和Main.C文件，实现功能:触摸按键按下时显示且只显示按下，并将采样的电压值打印出来，松开时显示且只显示松开，并将采样的电压值打印出来；


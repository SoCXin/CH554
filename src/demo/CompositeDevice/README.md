# CH554 USB Composite Device Demo (USB�����豸��ʾ����)

This demo emulates a USB composite device, which has 3 interface available (����ʾ����ģ����һ������3���ӿڵ�USB�豸):
* USB Mass Storage Device (USB MSD��USB�����������豸������U����)
* USB Keyboard (USB����)
* USB Vendor-Define HID (�����Զ����USB HID�豸)

Author(����): Rikka0w0 (С����)

* `keilc51\CH554.H`, `Delay.C` and `Delay.h` comes from official CH554 demo (WCH), the USB MSD implementation is inspired by the USB MSD demo for STM32 (ST). 
(`keilc51\CH554.H`, `Delay.C`��`Delay.h`�Ǵ�WCH�ٷ���ʾ����������ȡ�ģ�U�̲��ֳ���ο���STM32��USB MSDʾ��)
* All file in folder `includes` comes from Github repository [Blinkinlabs's ch554_sdcc](https://github.com/Blinkinlabs/ch554_sdcc).
(`includes`�ļ����е��ļ��Ǵ�[Blinkinlabs's ch554_sdcc](https://github.com/Blinkinlabs/ch554_sdcc)�︴�Ƶ�)
* Compiler/IDE: Keil uVersion & SDCC. (������/����������Keil �Vision��SDCC)
* A Wiki page describes how to setup SDCC on Windows and Linux. (Wiki�л���������Windows��Linux�ϴSDCC���뻷��)
* Feel free to use this demo as the template/start of a open-source or non-commercial project, modifying source code and republishing is allowed.
(���ڿ�Դ��Ŀ�ͷ���ҵ��Ŀ���������ñ���ʾ������Ϊ������ģ�壬���������޸Ĳ����·�����ݴ���)
* However you __MUST__ contact the author for permission prior to use this demo for commercial purposes.
(__���������ҵĿ�ĵĻ���������ǰ�õ����ߵ�����__)

__BadApple.zip contains a funny demo which can play the BadApple video on a SDD1306 128x64 OLED screen, the OLED screen is controlled via I2C, 
check out `I2c.c` for details about hardware configuration. (BadApple.zip����һ����Ȥ����ʾ��������SDD1306 128x64 OLED��Ļ�ϲ���BadApple��Ƶ��OLED��Ļͨ��I2C���ƣ���`I2c.c`�а������������Ļ����Ϣ)__


# Hardware Setup(Ӳ������):
* The hardware is based on the minimal circuit setup of CH554
(Ӳ������CH554����Сϵͳ)
* Chip is directly powered by Vbus, which is approximately 5V
(оƬֱ����Vbus��������Լ��5V)
* P1.5 = I2C SDA, P1.4 = I2C SCL, defined in `i2c.c`, each pin is pull-up by a 1k resistor to 5V.
(I2C���Ŷ�����`i2c.c`���棬ÿ���Ŷ�Ҫһ��1k���������裬������5V)
* Pin 1 to pin 4 of 24LC512 are connected to ground, Pin 8 connect to 5V, Pin5 is I2C SDA and Pin6 is I2C SCL, Pin7 is floating.
(24LC512 EEPROM��1��4�Ŷ��ӵأ�8������5V��5�Ŷ�ӦI2C SDA��6�Ŷ�ӦI2C SCL���߽�����) 
* Led1 is connected between 5V and P1.1 via a 1k resistor, it indicates R/W operations.
(Led21 ͨ��1k�������5V��P1.1֮�䣬����ָʾ��д����)
* Led2 is connected between 5V and P1.0 via a 1k resistor, it lights up when the MSD is ejected.
(Led2 ͨ��1k�������5V��P1.0֮�䣬�������������豸������ʱ����)

# Capabilities(������ʲô):
## USB Mass Storage Device (USB�����������豸)
* Emulate a 512Kib I2C EEPROM 24LC512 as a 64KB USB Drive
(��512Kib��I2C����EEPROM 24LC512ģ����һ��64KB��U��)
* Read, write, delete and format operations are fully supported.
(��ȫ֧�ָ��ֶ�дɾ�����и�ʽ������)
* Support safe media ejection in Windows, Linux and Mac OS X
(��Windows, Linux��Mac OS X��֧�ְ�ȫ��������)
* Use USB Endpoint 3 IN and OUT, Interface 2, Bulk-only transfer
(ʹ���˶˵�3��IN��OUT��2�Žӿڣ�BOT����)
## USB Keyboard (USB����)
* Simulate key press and release, and send them to the host.
(����ģ����̰�����������������)
* Use USB Endpoint 1 IN, Interface 1, Interrupt transfer
(ʹ���˶˵�2��IN��1�Žӿڣ� �жϴ���)
## USB Vendor-Define HID (�����Զ����USB HID�豸)
* Exchange data (receive and send) with host, up to 64 bytes each time
(���Ժ������������ݣ�ÿ�����64�ֽ�)
* Use USB Endpoint 2 IN, Interface 0, Interrupt transfer
(ʹ���˶˵�2��IN�� 0�Žӿڣ��жϴ���)
## UART (����)
* UART0, no function re-mapping (0�Ŵ��ڣ�û��io��ӳ��)
* Exchange data (receive and send) with host (���Ժ�������������)
* Support printf (֧��printf)
## I2C
* CH55x does not have built-in I2C peripheral (CH55xϵ��ľ������I2Cͨ������)
* Implement and emulate a I2C peripheral with GPIO (��GPIO��ģ��I2C����ͨ��)

# File Structure(�ļ��ṹ):
## main.c
* void main(void) {}
* USB Device Interrupt Entry(USB�豸�жϺ������)
## Delay.c Delay.h
* Delay (��ʱ����)
## ch554_platform.h
* Define uint8_t, uint32_t e.t.c (����uint8_t, uint32_t�ȵȱ�׼����)
* Handle the difference between Keil C51 and SDCC
(����Keil C51��SDCC������֮��Ĳ���)
* `U16B0` returns the lowest byte of a 16-bit integer, regardless of endian, similar defination for `U16B1`, `U32B0` e.t.c
(`U16B0`�᷵��һ��16λ�����ĵ��ֽڣ�����޹أ�`U16B1`, `U32B0`��Ҳ�����ƹ���)
* `U16_XBig` converts a big-endian 16-bit integer to fit the local endian, vise versa, similar defination for `U16_XLittle`, `U32_XBig` and `U32_XLittle`.
(`U16_XBig`���ڽ�һ����˴����16λ��ת���ɵ�ǰ�Ķ˷�ʽ��Ҳ�������ڷ���ת����`U16_XLittle`, `U32_XBig`��`U32_XLittle`����������)
* Instead of using `sbit led=P1^1`, use `SBIT(var, port, bin)` to declare a bit variable, for example, `SBIT(led, GPIO1, 1)`, this facilitates compilation under different compilers.
(�����`SBIT(var, port, bin)`������λ����������`SBIT(led, GPIO1, 1)`������`sbit led=P1^1`�������������ڲ�ͬ�������±������)
## ch554_conf.c ch554_conf.h
* Configure system clock (����ϵͳʱ��)
* Initialize USB Device (��ʼ��USB�豸)
* Initialize UART0 (��ʼ������0)
* Set system clock frequency and UART0 baud rate in ch554_conf.h
(��ch554_conf.h������ϵͳʱ��Ƶ�ʺ�UART0�Ĳ�����)
## i2c.c i2c.h
* Emulate a I2C bus host with GPIO (��GPIO��ģ��һ��I2C��������)
* `I2C_DELAY(void)` controls the I2C clock frequency
* `I2C_WriteByte()` sends the data byte in `I2C_Buf` to I2C bus and return the ACK status in bit 0 of `I2C_Buf` then release the I2C bus,
0 means ACK and 1 means NACK. 
(`I2C_WriteByte()`���`I2C_Buf`���һ���ֽڷ��͵�I2C�����ϲ���`I2C_Buf`�����λ����ACK��״̬Ȼ���ͷ�I2C���ߣ�0ΪACK��1ΪNACK) 
* `I2C_ReadByte(void)` reads a byte from I2C bus and store it in `I2C_Buf`. 
(`I2C_ReadByte(void)`��I2C�����϶�һ���ֽ�Ȼ�����`I2C_Buf`����)
## eeprom.c eeprom.h
* Control read and write of EEPROM (����EEPROM�Ķ�д)
* Transfer length up to 128 bytes (��дÿ�����128�ֽ�)
## usb_it.c
* USB interrupt service routine (USB�жϴ�����)
* Handle USB bus reset/suspend/wakeup (����USB��������/����/����)
* Dispatch incoming requests to EndPoint service functions (����������������ַ����˵�Ĵ�����)
## usb_endp.h
* Declear EndPoint buffers (�����˵�Ļ���)
* Toggle certain EndPoint service function (�������߹ر���صĶ˵㴦����)
## usb_endp.c
* Define EndPoint buffers (����˵�Ļ����Լ���С)
* `USB_EP_HALT_SET(ep)` and `USB_EP_HALT_CLEAR(ep)` stall or restore an EndPoint as the host requests 
(`USB_EP_HALT_SET(ep)`��`USB_EP_HALT_CLEAR(ep)`���������������stall���߻ָ��˵�)
* Optionally, add your EndPoint service functions here (���Ը����԰�USB�Ķ˵㴦������������)
## usb_ep0.c
* Contain service routine for EndPoint 0 SETUP/IN/OUT
(�����˵�0��SETUP/IN/OUT����Ĵ�����)
* Handle requests sent by host during enumeration phase
(��ö�ٵ�ʱ�����Ӧ����������)
## usb_desc.h
* Define the total length of Config Descriptor, including Interface Descriptor e.t.c (�����������������ܴ�С�������ӿ���������)
* Define the total number of String Descriptor (�����ַ�������������)
* Define length of HID Report Descriptors (�������HID�����������Ĵ�С)
## usb_desc.c
* Define Device Descriptor (�����豸������)
* Define Configuration Descriptor and Interface Descriptor (�������úͽӿ�������)
## usb_hid_desc.c
* Define HID Report Descriptors (�������HID����������)
## usb_string_desc.c
* Define custom String Descriptors (�����Զ�����ַ�������)
* String Descriptor 0 is reserved for language configuration (0���ַ���������Ϊ���Ա�ʶ������)
## usb_hid_keyboard.h
* `USB_Keyboard_SendKey()` sends a key combination to the host, the first parameter specifies the modifier, e.g. KBD_LCTRL for left control, combination is supported, 
the second parameter determines which key is pressed, e.g. 0x04 for letter a on keyboard. Check out [HID protocol](https://docs.mbed.com/docs/ble-hid/en/latest/api/md_doc_HID.html) for details.
(`USB_Keyboard_SendKey()`����������һ��������ϣ���һ���������������η�������KBD_LCTRL������CTRL��������֧����ϡ��ڶ����������������ĸ�����������0x04��Ӧ�ż����ϵ�A��������������[HIDЭ��](https://docs.mbed.com/docs/ble-hid/en/latest/api/md_doc_HID.html)����)
## usb_bot.h
* Forward EndPoint IN/OUT buffer, abstract BOT layer behavior, see section `// BOT_USB Config`
(ת���˵�Ļ���Ķ��壬����BOT�㣬�μ�`// BOT_USB Config`�����ǲ���)
* It's possible to migrate the MSD function to other devices
(���Խ����������湦����ֲ�������豸��)
## usb_bot.c
* Mass storage device IN/OUT service routine (�����������豸��IN/OUT��������)
* Implements a BOT state machine (ʵ����һ��BOT״̬��)
* `CBW_Decode` translates USB packets to SCSI instructions (`CBW_Decode`��USB������ΪSCSIָ��)
* `Transfer_Data_Request` sends some data to host as reply (`Transfer_Data_Request`����������һЩ������Ϊ�ظ�)
* `Reply_Request` sends the content stored in `BOT_Tx_Buf` to host as reply (`Reply_Request`��`BOT_Tx_Buf`�������������������Ϊ�ظ�)
* `Transfer_Failed_ReadWrite` sends a empty packet to host and the device will send its CSW in the next transaction
(`Transfer_Failed_ReadWrite`����������һ���հ�������һ������������CSW״̬)
* `Set_CSW` sets the CSW status, by set `Send_Permission` to 1, it will send CSW immediately.
(`Set_CSW`��������CSW״̬����`Send_Permission`��Ϊ1�����̷���CSW)
## usb_scsi.c
* Process SCSI inquiry and instructions
(����SCSI�������ָ��)
* Read and Write Operations are controlled by a state machine, see section `// SCSI R/W state machine`
(��д����һ��״̬�����Ƶģ��μ�`// SCSI R/W state machine`)
## usb_scsi.h
* Define SCSI instruction codes, sense keys, e.t.c.
(����SCSIָ�����ֵ��)
## usb_mal.h
* Define number of LUNs (Logic unit)
(�������߼���Ԫ������)
* Declare functions that are necessary for MSD to work
(������һЩMSD������������Ҫ�ĺ���)
## usb_mal.c
* Implement all functions declared in `usb_mal.h`
(ʵ��������usb_mal.h�ﶨ��ĺ���)
* Define `Inquiry Data`
(����`Inquiry Data`��������������Ʒ��֮���)
## Files in folder `OLDE` (OLED�ļ����е��ļ�)
* `sdd1306.h` and `sdd1306.c` provides functions to initialize SDD1306-based OLED screen and chunk programming the display pattern.
(`sdd1306.h`��`sdd1306.c`�ṩ�˻���SDD1306��OLED��Ļ�ĳ�ʼ���Ϳ�����ʾģʽ�Ĺ���)
* `sdd1306_ascii.h` and `sdd1306_ascii.c` provides functions to display ASCII characters on OLED screen.
(`ssd1306 ascii.h`��`ssd1306 ascii.c`�ṩ��OLED��Ļ����ʾASCII�ַ��Ĺ���)

# Notes:
* The only difference between CH554 and CH552 is that, CH552 only supports USB device mode while CH554 can also be programmed as a Host. 
So this demo may work on CH552 as well. (CH552ֻ����ΪUSB���豸����CH554��������ΪUSB��������������оƬΨһ��������˱�Demo����Ҳ����CH552����������)
* In this demo, __the I2C EEPROM is compolsory__, without it, the enumeration will not succeed. If you don't have the EEPROM, to get rid of it,
comment out the EEPROM read and write operation in `LUN_Write` and `Lun_Read` in `usb_mal.c`.
(�����I2C��EEPROM�Ǳ���ģ�û�����豸�᲻������ö�٣������������`usb_mal.c`ע�͵�`LUN_Write` �� `Lun_Read`����Ķ�д����)
* 8051 systems including CH554 is big-endian while x86 and ARM processors are little-endian.
(8051ϵͳ����CH554�Ǵ�˴洢�ģ������ݵĸ�λ���ڵ��ڴ��ַ�У���x86��ARM����������С�˴洢��)
* USB packets are little-endian however the attached SCSI instructions are big-endian, keep this in mind!
(USB������С�˵�Ȼ��������SCSIָ���Ǵ�˵ģ��ر���Ҫע�⣡) 
* SDCC requires that all interrupt service functions must be written inside the same .c file containing `void main(void)`, 
otherwise SDCC can not find them. According to official SDCC documentation, it's not a bug but a feature. Keil C51 doesn't have this limitaion.
(SDCCҪ���жϴ����������main��������һ��.c�ļ��У�����SDCCû�취�ҵ���Щ����������SDCC�ٷ��ĵ�������һ�����Բ���Bug��Keil C51������û����������)
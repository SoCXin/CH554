/********************************** (C) COPYRIGHT ******************************
* File Name          :Compound_Dev.C											
* Author             :                                                      
* Version            : V1.0                                                     
* Date               : 2017/03/15                                               
* Description        : A demo for USB compound device created by CH554, support 
					   keyboard and mouse, and HID compatible device.           
********************************************************************************/
#include 	<stdio.h>
#include 	"CH554.H"

#include 	"Debug.H"
#include "Touch_Key.H"
#include	"Compound.H"

extern UINT8 	FLAG;												  // Trans complete flag
extern UINT8 	EnumOK;												// Enum ok flag
UINT16I 	TouchKeyButton = 0;							

void main( void )
{
  CfgFsys();                                //Configure sys
	mDelaymS(5);                              //
  mInitSTDIO( );                            // Init UART0

#if	DE_PRINTF
    printf( "Start config.\r\n" );
    printf( "Init USB device.\r\n" );
#endif
	USBDeviceInit();                          // Configure the USB module,the Endpoint and the USB Interrupt
  EA = 1;	
	UEP1_T_LEN = 0;                           // Reset the trans length register
  UEP2_T_LEN = 0;                                                  
  FLAG = 0;
	EnumOK = 0;
  TouchKeyQueryCylSet1Or2ms(1);	            //set query cycle
  TouchKeyChanelSelect(3);                  //set query chanel	
    while(1)
	{
       
        if( EnumOK == 1 )
        {					
            HIDValueHandle();				
        }
        else
        {
            if(TKEY_CTRL&bTKC_IF)           //wait query finsh,max 2ms ��ȡ��ֵ��׼ֵ�����������
            {							
            TouchKeyButton = TKEY_DAT;      //	
#ifdef DE_PRINTF
            printf("A.=  %04x\n",TouchKeyButton&0x7FFF);		
#endif	
            }							
        }					
    }
}

/**************************** END *************************************/

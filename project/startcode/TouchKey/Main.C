
/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.C
* Author             : WCH
* Version            : V1.2
* Date               : 2019/07/22
* Description        : CH554 触摸按键中断和查询方式进行采集并报告当前采样通道按键状态，包含初始化和按键采样等演示函数  
                       串口输出按键状态
*******************************************************************************/
#include "..\Public\CH554.H"                                                   
#include "..\Public\Debug.H"
#include "TouchKey.H"
#include "stdio.h"

#pragma  NOAREGS

/*******************************************************************************
Input channel as below:

 bTKC_CHAN2 |bTKC_CHAN1	|bTKC_CHAN0	|	CHANNEL				| PIN		
 -----------+-----------+-----------+-----------------------+------------
 	0		|	0		|	0		|	no channel			| ****		
 	0		|	0		|	1		|	TIN0				| P1.0		
 	0		|	1		|	0		|	TIN1				| P1.1		
 	0		|	1		|	1		|	TIN2				| P1.4		
 	1		|	0		|	0		|	TIN3				| P1.5		
 	1		|	0		|	1		|	TIN4				| P1.6		
 	1		|	1		|	0		|	TIN5				| P1.7		
	1		|	1		|	1		|	Enable touch core	| no channel
*******************************************************************************/

void main()
{
	CfgFsys();																/* Freq = 12MHz. */
	mDelaymS(5);

	mInitSTDIO();															/* Baud 57600 bps. */
	printf("Debug data:"__DATE__",Debug time:"__TIME__"\n");
	
	TK_Init( BIT4+BIT5+BIT6+BIT7,  1, 0 );		/* Choose TIN2, TIN3, TIN4, TIN5 for touchkey input. enable interrupt. */
	TK_SelectChannel(0);											/* NOTICE: ch is not compatible with the IO actually. */
//	EA = 1;																	  /* Enable global interrupt. */
	while ( 1 )
	{
          TK_Measure();	
	}
	
}

#ifndef __TEMPUSART_H
#define __TEMPUSART_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//��?3��D��??1??��?�㨺1��?��??��?-����??D��?����?2?��?��?����???����?o?��?��?
//Mini STM32?a�����?
//ADC ?y?���䨲??			   
//?y��??-����@ALIENTEK
//??��???��3:www.openedv.com
//DT??��??��:2010/6/7 
//��?��?��oV1.0
//��?����?����D��?�̨���?��????��
//Copyright(C) ?y��??-���� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 		 
/*void  Adc_Init(void); 
u16 Get_Adc(u8 ch)  ;
u16 Get_Adc_Average(u8 ch,u8 times);
*/
float Get_Temprate(void);			//??��??��2????����??D?��???��?��
void T_Adc_Init(void); //ADC�����̨�3?��??��
u16  T_Get_Adc(u8 ch); //??��??3??�����̨�?��  
u16  T_Get_Adc_Average(u8 ch,u8 times);//��?��??3??�����̨�10��?2��?����????��?�� 	  
void uart_init(u32 a);
void Timerx_Init(u16 arr,u16 psc);
#endif 



#ifndef __TEMPUSART_H
#define __TEMPUSART_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//¡À?3¨¬D¨°??1??¡ì?¡ã¨º1¨®?¡ê??¡ä?-¡Á¡Â??D¨ª?¨¦¡ê?2?¦Ì?¨®?¨®¨²???¨¹¨¨?o?¨®?¨ª?
//Mini STM32?a¡¤¡é¡ã?
//ADC ?y?¡¥¡ä¨²??			   
//?y¦Ì??-¡Á¨®@ALIENTEK
//??¨º???¨¬3:www.openedv.com
//DT??¨¨??¨²:2010/6/7 
//¡ã?¡À?¡êoV1.0
//¡ã?¨¨¡§?¨´¨®D¡ê?¦Ì¨¢¡ã?¡À????¡ê
//Copyright(C) ?y¦Ì??-¡Á¨® 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 		 
/*void  Adc_Init(void); 
u16 Get_Adc(u8 ch)  ;
u16 Get_Adc_Average(u8 ch,u8 times);
*/
float Get_Temprate(void);			//??¨¨??¨²2????¨¨¡ä??D?¡Â???¨¨?¦Ì
void T_Adc_Init(void); //ADC¨ª¡§¦Ì¨¤3?¨º??¡¥
u16  T_Get_Adc(u8 ch); //??¦Ì??3??¨ª¡§¦Ì¨¤?¦Ì  
u16  T_Get_Adc_Average(u8 ch,u8 times);//¦Ì?¦Ì??3??¨ª¡§¦Ì¨¤10¡ä?2¨¦?¨´¦Ì????¨´?¦Ì 	  
void uart_init(u32 a);
void Timerx_Init(u16 arr,u16 psc);
#endif 



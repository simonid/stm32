#ifndef __TEMDMA_H
#define __TEMDMA_H
#include "sys.h"
void ADCTEMP_Config(void);
//void TIM3_Init(u16 arr,u16 psc);
u16 T_Get_Adc(u8 ch)  ;
u16 T_Get_Temp(void);
u16 T_Get_Adc_Average(u8 ch,u8 times);
short Get_Temprate(void);
void DMA_Config(void);
void Sys_Sleepy(void);
void Sys_Enter_Sys_Sleepy(void);
void Key_Init(void);
void Delayms(u16 time);
#endif

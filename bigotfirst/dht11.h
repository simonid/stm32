#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT11������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO��������
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}   //12:4*3
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
////IO��������											   
#define	DHT11_DQ_OUT PBout(11) //���ݶ˿�	PA0   PB11
#define	DHT11_DQ_IN  PBin(11)  //���ݶ˿�	PA0 
//void Timerx_Init(u16 arr,u16 psc);
//void TIM3_Int_Init(u16 arr,u16 psc);
u8 DHT11_Init(void);//��ʼ��DHT11
uint16_t DHT11_Read_Data(float *temp,float *humi);//��ȡ�¶�
//uint16_t DHT11_Read_Data2(uint16_t *humi);//��ȡʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif
















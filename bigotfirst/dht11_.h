#ifndef __DHT11__H
#define __DHT11__H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DHT11数字温湿度传感器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO方向设置
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}   //12:4*3
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
////IO操作函数											   
#define	DHT11_DQ_OUT PBout(11) //数据端口	PA0   PB11
#define	DHT11_DQ_IN  PBin(11)  //数据端口	PA0 
//void Timerx_Init(u16 arr,u16 psc);
//void TIM3_Int_Init(u16 arr,u16 psc);
u8 DHT11_Init(void);//初始化DHT11
uint16_t DHT11_Read_Data(float *temp,float *humi);//读取温度
//uint16_t DHT11_Read_Data2(uint16_t *humi);//读取湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif
















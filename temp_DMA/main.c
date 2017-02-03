#include"delay.h"
#include "sys.h"
#include "usart.h"
#include "temDMA.h"

short temp;
void delayus(u16 time)
{
	u16 i=0;
	while(time--)
	{
		i=10;
		while(i--);
	}
}
void delayms(u16 time)
{
	u16 i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
}
int main()
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	uart_init(115200);
	//TIM3_Init(6999,7999);
	ADCTEMP_Config();
	DMA_Config();
	 //Key_Init();
		Key_Init(); //待机唤醒初始化
	//printf("now is working\r\n");
	printf("now still in sleep\r\n");   //假如按了按键先打印这里，睡眠模式初始化的函数相当于加了断点
		delayms(2000);
	 
	temp=Get_Temprate();   //可以注意到这上下一段实际上在睡眠是不工作的
		printf("now the temp is:%d\r\n",temp);  
		
		delayms(3000);
	while(1)
	{
		temp=Get_Temprate();
		printf("now is working\r\n");
		delayms(2000);
		printf("now the temp is:%d\r\n",temp);
		
		delayms(3000);
	}
}


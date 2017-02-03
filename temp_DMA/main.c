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
		Key_Init(); //�������ѳ�ʼ��
	//printf("now is working\r\n");
	printf("now still in sleep\r\n");   //���簴�˰����ȴ�ӡ���˯��ģʽ��ʼ���ĺ����൱�ڼ��˶ϵ�
		delayms(2000);
	 
	temp=Get_Temprate();   //����ע�⵽������һ��ʵ������˯���ǲ�������
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


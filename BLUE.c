#include"stm32f10x.h"
#include "stdio.h"	
#include "sys.h" 
#include"LED.h"
#include"BLUE.h"
unsigned char temp=0;
 unsigned char buff[6];
unsigned char s=0;
u16 USART_RX_STA=0;       //接收状态标记	 
void USART1_Config(u32 bound)
{
	/*  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);*/
	 GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE); 
		
/*	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/
	}

/*void qianjin()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_5);
	
}
void houtui()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_1);
}
void zuozhuan()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);
}
void youzhuan()
{
 GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_5);
}
void tingzhi()
{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_1|GPIO_Pin_3);
}  */
/*void USART1_IRQHandlerr()
{
//	unsigned char i;
	Init_LEDpin();
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{
		if(USART_ReceiveData(USART1)==65)  //A
		{
			buff[0]=1; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==66)   //B
		{
			buff[0]=2; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==67)  //C
		{
			buff[0]=3; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==68)   //D
		{
			buff[0]=4; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==69)   //E
		{
			buff[0]=5; USART_SendData(USART1,buff[0]);
		}
		
	}
*/
void USART1_IRQHandler(void)       //串口接收中断，并将接收到得数据发送出
{
 u16 temp_trx;
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断 是否 接收中断  
 {
  temp_trx = USART_ReceiveData(USART1);
  USART_SendData(USART1,temp_trx);
	//SetJointAngle(temp_trx,0);
	 USART_ClearITPendingBit(USART1, USART_IT_RXNE);                                                                                                                                                                                                                
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{
		if(USART_ReceiveData(USART1)==65)  //A
		{
			buff[0]=1; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==66)   //B
		{
			buff[0]=2; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==67)  //C
		{
			buff[0]=3; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==68)   //D
		{
			buff[0]=4; USART_SendData(USART1,buff[0]);
		}
		if(USART_ReceiveData(USART1)==69)   //E
		{
			buff[0]=5; USART_SendData(USART1,buff[0]);
		}
     while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//判断 发送标志 
 }
}
	//buff[0]=USART_ReceiveData(USART1);
	
	/*if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
				{
					USART_ClearITPendingBit(USART1,USART_IT_RXNE);
				}
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
		i=USART_ReceiveData(USART1);
		if(i=='a'){ s=1;}
		if((s==1)&&(i!='\0'))
		{
			buff[temp++]=i;
			if(temp>2)
				if(buff[2]=='b')
				{
					qianjin();
					
				}
				if(buff[2]=='c')
				{
					houtui();
				}
				if(buff[3]=='d')
				{
					tingzhi();
				}
				if(buff[4]=='e')
				{
					zuozhuan();
				}
				if(buff[5]=='f')
				{
					youzhuan();
				}
				if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
				{
					USART_ClearITPendingBit(USART1,USART_IT_RXNE);
				}
				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		}
	}*/
}

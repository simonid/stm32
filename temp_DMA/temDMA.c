#include "temDMA.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
extern short temp;
void ADCTEMP_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	 //ADC_InitStructure.ADC_NbrOfChannel = 3;//转换通道为通道1
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_TempSensorVrefintCmd(ENABLE);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_16,2,ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_17,3,ADC_SampleTime_239Cycles5);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));	
	//ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address;
//	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize=3;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc=DAM_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

/*void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1))
	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);
		ADC_OK=TRUE;
	}
}*/
void Key_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;	 //PA1
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//上拉输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化IO	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;	 //PA4
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;//上拉输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化IO
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	  EXTI_InitStructure.EXTI_Line = EXTI_Line1;	//设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //上升沿触发
 	EXTI_InitStructure.EXTI_LineCmd =ENABLE;// DISABLE;
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;	//设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //上升沿触发
 	EXTI_InitStructure.EXTI_LineCmd =ENABLE;// DISABLE;
	EXTI_Init(&EXTI_InitStructure);	// 初始化外部中断
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)!=1) Sys_Sleepy();    //不是开机,进入待机模式  
}

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=arr;
	TIM_TimeBaseStructure.TIM_Prescaler=psc;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler(void)   //TIM3
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
		//LED1=!LED1;
			printf("now the temp is:%d\r\n",temp);
		}
}

u16 T_Get_Adc(u8 ch)   
	{
 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	return ADC_GetConversionValue(ADC1);	
	}


u16 T_Get_Temp(void)
	{
	u16 temp_val=0;
	u8 t;
	for(t=0;t<10;t++)
		{
		temp_val+=T_Get_Adc(ADC_Channel_16);	  //TampSensor
		delay_ms(5);
		}
	return temp_val/10;
	}

 
u16 T_Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=T_Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	   


short Get_Temprate(void)	
{
	u32 adcx;
	short result;
 	double temperate;
	adcx=T_Get_Adc_Average(ADC_Channel_16,20);
	temperate=(float)adcx*(3.3/4096);		
	temperate=(1.43-temperate)/0.0043+25;		 
	result=temperate;						
	return result;
}

void Sys_Sleepy(void)
{
	SCB->SCR|=0x00;
	
	#if defined ( __CC_ARM   )  
	__force_stores();
	#endif
	__WFI();
}
void Sys_Enter_Sys_Sleepy(void)
{
	Sys_Sleepy();
}

void EXTI1_IRQHandler(void)
{ 		    		    				     		    
	EXTI_ClearITPendingBit(EXTI_Line1); // 清除LINE1上的中断标志位	
		  SCB->SCR |=SCB_SCR_SEVONPEND;
	  //  Sys_Enter_Sys_Sleepy();
	printf("EXTI_LINE1\r\n");
	//if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)//关机?
	//{		
			delay_ms(200);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)
			{
				//LED0=0;
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				Sys_Enter_Sys_Sleepy();
			}
	//} 
			else         //LED1=0;
     GPIO_SetBits(GPIOA,GPIO_Pin_8);
			
} 
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);
		SCB->SCR |=SCB_SCR_SEVONPEND;
	printf("EXTI LINE4\r\n");
}

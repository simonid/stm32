#include "tempusart.h"
#include "delay.h"
#include "sys.h"
#include"usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

//float tem;
		   
//3?ê??ˉADC
//?aà??ò????ò?1??òí¨μà?aày
//?ò????è????a??í¨μà0~3	
/*void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	//ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);		//ADC1复位借宿

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M
	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  //	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);  //ADC规则序列配置

	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//重置指定的ADC1的校准寄存器
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1重置校准寄存器的状态,设置状态则等待
	
	ADC_StartCalibration(ADC1);		//开始指定ADC1的校准状态
 
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,规则采样顺序值为1,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} */


void T_Adc_Init(void)  //ADCí¨μà3?ê??ˉ
{
	ADC_InitTypeDef ADC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ê1?üGPIOA,ADC1í¨μàê±?ó
  
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //·??μòò×ó6ê±?ó?a72M/6=12MHz
 ADC_DeInit(ADC1);  //??íaéè ADC1 μ?è?2???′??÷??éè?aè±ê??μ
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC1¤×÷?￡ê?:ADC1oíADC21¤×÷?ú?àá￠?￡ê?
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//?￡êy×a??1¤×÷?úμ￥í¨μà?￡ê?
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//?￡êy×a??1¤×÷?úμ￥′?×a???￡ê?
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//×a??óéèí?t??2?ê?ía2?′￥·￠???ˉ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADCêy?Yóò????
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//?3Dò??DD1??ò×a??μ?ADCí¨μàμ?êy??
	ADC_Init(ADC1, &ADC_InitStructure);	//?ù?YADC_InitStruct?D???¨μ?2?êy3?ê??ˉíaéèADCxμ???′??÷

	ADC_TempSensorVrefintCmd(ENABLE); //?a???ú2????è′??D?÷
	
 
	ADC_Cmd(ADC1, ENABLE);	//ê1?ü???¨μ?ADC1

	ADC_ResetCalibration(ADC1);	//???????¨μ?ADC1μ??′????′??÷

    while(ADC_GetResetCalibrationStatus(ADC1));	//??è?ADC1????D￡×???′??÷μ?×′ì?,éè??×′ì??òμè′y

	ADC_StartCalibration(ADC1);	 //

	while(ADC_GetCalibrationStatus(ADC1));		//??è????¨ADC1μ?D￡×?3ìDò,éè??×′ì??òμè′y
}
u16 T_Get_Adc(u8 ch)   
	{
 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCí¨μà3,μúò???×a??,2é?ùê±???a239.5?ü?ú	  			    
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ê1?ü???¨μ?ADC1μ?èí?t×a?????ˉ1|?ü
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//μè′y×a???áê?
	return ADC_GetConversionValue(ADC1);	//·μ??×??üò?′?ADC11??ò×éμ?×a???á1?
	}

//μ?μ?ADC2é?ù?ú2????è′??D?÷μ??μ
//è?10′?,è?oó???ù
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

 //??è?í¨μàchμ?×a???μ
//è?times′?,è?oó???ù
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

//μ?μ????è?μ
//·μ???μ:???è?μ(à?′óá?100±?,μ￥??:??.)
float Get_Temprate(void)	//??è??ú2????è′??D?÷???è?μ
{
	u32 adcx;
	short result;
 	double temperate;
	adcx=T_Get_Adc_Average(ADC_Channel_16,20);	//?áè?í¨μà16,20′?è????ù
	temperate=(float)adcx*(3.3/4096);		//μ??1?μ 
	temperate=(1.43-temperate)/0.0043+25;	//×a???a???è?μ 	 
	result=temperate;					//例程是result=temperate*=100;，结果就是4位数	
	return result;
}

/*void Timerx_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ê±?óê1?ü

	TIM_TimeBaseStructure.TIM_Period = arr; //éè???ú??ò????üD?ê??t×°è????ˉμ?×??ˉ??×°????′??÷?ü?úμ??μ	 ??êyμ?5000?a500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //éè??ó?à′×÷?aTIMxê±?ó?μ?ê3yêyμ??¤·??μ?μ  10Khzμ???êy?μ?ê  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //éè??ê±?ó·???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?òé???êy?￡ê?
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //?ù?YTIM_TimeBaseInitStruct?D???¨μ?2?êy3?ê??ˉTIMxμ?ê±???ùêyμ￥??
 
	TIM_ITConfig(  //ê1?ü?ò??ê§?ü???¨μ?TIM?D??
		TIM4, //TIM2
		TIM_IT_Update  |  //TIM ?D???′
		TIM_IT_Trigger,   //TIM ′￥·￠?D???′ 
		ENABLE  //ê1?ü
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?è??ó??è??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //′óó??è??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQí¨μà±?ê1?ü
	NVIC_Init(&NVIC_InitStructure);  //?ù?YNVIC_InitStruct?D???¨μ?2?êy3?ê??ˉíaéèNVIC??′??÷

	TIM_Cmd(TIM4, ENABLE);  //ê1?üTIMxíaéè
							 
}*/

/*void TIM4_IRQHandler(void)   //TIM2?D??
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //?ì2é???¨μ?TIM?D??·￠éúó?·?:TIM ?D???′ 
		{
		//temp=Get_Temprate();
	printf("   Now temp is  %f  \r\n",temp);
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //??3yTIMxμ??D??′y′|àí??:TIM ?D???′ 
		}
}*/


/*****************************************************************************
*****************************************************************************/
//′??úGPIO?ú????
/*void uart_init(u32 a)
{

	GPIO_InitTypeDef GPIO_InitStructure;
 USART_InitTypeDef USART_InitStructure; 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ê1?ü′??ú1μ?GPIOê±?ó
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOD, &GPIO_InitStructure);
// GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);  
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //?′ó?í?íìê?3?
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //Dü??ê?è?
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 
         
 USART_InitStructure.USART_BaudRate = a;      //éè?¨2¨ì??ê
 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //′?ê?êy?Y??êy
 USART_InitStructure.USART_StopBits = USART_StopBits_1;   //í￡?1??1
 USART_InitStructure.USART_Parity = USART_Parity_No;    //2?ó?D￡?é??
 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//2?ó?á÷á?????
 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ê1ó??óê?oí·￠?í1|?ü
 USART_Init(USART1, &USART_InitStructure);       //3?ê??ˉ′??ú1
 USART_Cmd(USART1,ENABLE);            //′??ú1ê1?ü
 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     //ê1?ü′??ú1 ?á?D??
  
	NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);     //?è??ó??èè¨2￡?′óó??è??2??
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;    //?a′??ú?D??1
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;   //???¨?à??ó??è??±e1
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //???¨?àó|ó??è??±e0
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)       //′??ú?óê??D??￡?2￠???óê?μ?μ?êy?Y·￠?í3?
{
 u16 temp_trx;
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//?D?? ê?·? ?óê??D??  
 {
  temp_trx = USART_ReceiveData(USART1);
  USART_SendData(USART1,temp_trx);
	//SetJointAngle(temp_trx,0);
	 //short temp;
	 //temp=Get_Temprate();
	 printf("   Now temp is  %d  \r\n,temp");
     while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//?D?? ·￠?í±ê?? 
 }
}
*/



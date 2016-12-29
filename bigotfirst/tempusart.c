#include "tempusart.h"
#include "delay.h"
#include "sys.h"
#include"usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

//float tem;
		   
//3?��??��ADC
//?a��??��????��?1??�������̨�?a��y
//?��????��????a??�����̨�0~3	
/*void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	//ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);		//ADC1��λ����

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  //	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);  //ADC������������

	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
 
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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


void T_Adc_Init(void)  //ADC�����̨�3?��??��
{
	ADC_InitTypeDef ADC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //��1?��GPIOA,ADC1�����̨�����?��
  
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //��??�̨�������6����?��?a72M/6=12MHz
 ADC_DeInit(ADC1);  //??��a���� ADC1 ��?��?2???��??��??����?a������??��
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC1�����?�꨺?:ADC1o��ADC21�����?��?������?�꨺?
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//?�꨺y��a??1�����?���̣������̨�?�꨺?
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//?�꨺y��a??1�����?���̣���?��a???�꨺?
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��a??��������?t??2?��?��a2?�䣤����???��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC��y?Y����????
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//?3D��??DD1??����a??��?ADC�����̨���?��y??
	ADC_Init(ADC1, &ADC_InitStructure);	//?��?YADC_InitStruct?D???����?2?��y3?��??����a����ADCx��???��??��

	ADC_TempSensorVrefintCmd(ENABLE); //?a???��2????����??D?��
	
 
	ADC_Cmd(ADC1, ENABLE);	//��1?��???����?ADC1

	ADC_ResetCalibration(ADC1);	//???????����?ADC1��??��????��??��

    while(ADC_GetResetCalibrationStatus(ADC1));	//??��?ADC1????D���???��??�¦�?���䨬?,����??���䨬??���̨���y

	ADC_StartCalibration(ADC1);	 //

	while(ADC_GetCalibrationStatus(ADC1));		//??��????��ADC1��?D���?3��D��,����??���䨬??���̨���y
}
u16 T_Get_Adc(u8 ch)   
	{
 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC�����̨�3,�̨���???��a??,2��?������???a239.5?��?��	  			    
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//��1?��???����?ADC1��?����?t��a?????��1|?��
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�̨���y��a???����?
	return ADC_GetConversionValue(ADC1);	//����??��??����?��?ADC11??��������?��a???��1?
	}

//��?��?ADC2��?��?��2????����??D?�¦�??��
//��?10��?,��?o��???��
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

 //??��?�����̨�ch��?��a???��
//��?times��?,��?o��???��
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

//��?��????��?��
//����???��:???��?��(��?�䨮��?100��?,�̣�??:??.)
float Get_Temprate(void)	//??��??��2????����??D?��???��?��
{
	u32 adcx;
	short result;
 	double temperate;
	adcx=T_Get_Adc_Average(ADC_Channel_16,20);	//?����?�����̨�16,20��?��????��
	temperate=(float)adcx*(3.3/4096);		//��??1?�� 
	temperate=(1.43-temperate)/0.0043+25;	//��a???a???��?�� 	 
	result=temperate;					//������result=temperate*=100;���������4λ��	
	return result;
}

/*void Timerx_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //����?����1?��

	TIM_TimeBaseStructure.TIM_Period = arr; //����???��??��????��D?��??t���㨨????����?��??��??����????��??��?��?����??��	 ??��y��?5000?a500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����??��?�������?aTIMx����?��?��?��3y��y��??�衤??��?��  10Khz��???��y?��?��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����??����?����???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?����???��y?�꨺?
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //?��?YTIM_TimeBaseInitStruct?D???����?2?��y3?��??��TIMx��?����???����y�̣�??
 
	TIM_ITConfig(  //��1?��?��??����?��???����?TIM?D??
		TIM4, //TIM2
		TIM_IT_Update  |  //TIM ?D???��
		TIM_IT_Trigger,   //TIM �䣤����?D???�� 
		ENABLE  //��1?��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?��??��??��??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�䨮��??��??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ�����̨���?��1?��
	NVIC_Init(&NVIC_InitStructure);  //?��?YNVIC_InitStruct?D???����?2?��y3?��??����a����NVIC??��??��

	TIM_Cmd(TIM4, ENABLE);  //��1?��TIMx��a����
							 
}*/

/*void TIM4_IRQHandler(void)   //TIM2?D??
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //?��2��???����?TIM?D??���騦����?��?:TIM ?D???�� 
		{
		//temp=Get_Temprate();
	printf("   Now temp is  %f  \r\n",temp);
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //??3yTIMx��??D??��y��|����??:TIM ?D???�� 
		}
}*/


/*****************************************************************************
*****************************************************************************/
//��??��GPIO?��????
/*void uart_init(u32 a)
{

	GPIO_InitTypeDef GPIO_InitStructure;
 USART_InitTypeDef USART_InitStructure; 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//��1?����??��1��?GPIO����?��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOD, &GPIO_InitStructure);
// GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);  
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //?�䨮?��?������?3?
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //D��??��?��?
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 
         
 USART_InitStructure.USART_BaudRate = a;      //����?��2����??��
 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //��?��?��y?Y??��y
 USART_InitStructure.USART_StopBits = USART_StopBits_1;   //����?1??1
 USART_InitStructure.USART_Parity = USART_Parity_No;    //2?��?D��?��??
 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//2?��?���¨�?????
 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //��1��??����?o������?��1|?��
 USART_Init(USART1, &USART_InitStructure);       //3?��??����??��1
 USART_Cmd(USART1,ENABLE);            //��??��1��1?��
 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     //��1?����??��1 ?��?D??
  
	NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);     //?��??��??������2��?�䨮��??��??2??
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;    //?a��??��?D??1
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;   //???��?��??��??��??��e1
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //???��?����|��??��??��e0
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)       //��??��?����??D??��?2��???����?��?��?��y?Y����?��3?
{
 u16 temp_trx;
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//?D?? ��?��? ?����??D??  
 {
  temp_trx = USART_ReceiveData(USART1);
  USART_SendData(USART1,temp_trx);
	//SetJointAngle(temp_trx,0);
	 //short temp;
	 //temp=Get_Temprate();
	 printf("   Now temp is  %d  \r\n,temp");
     while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//?D?? ����?������?? 
 }
}
*/



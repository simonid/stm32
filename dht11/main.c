//#include "led.h"
#include "delay.h"
//#include "key.h"
#include "sys.h"
//#include "lcd.h"
#include "usart.h"	 
#include "dht11.h" 	
 #include  "ds18b20.h"


	u8 temperature;  	    
	u8 humidity;  
 
 int main(void)
 {	 
	//u8 t=0;			    
  	   
 float Temp;
	delay_init();	    	 //?óê±oˉêy3?ê??ˉ	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	uart_init(115200);	 
	  TIM3_Int_Init(6000,8199);
	 //Timerx_Init(5000,7199); 
	 DHT11_Init();
	 delay_ms(200);
	 while(DS18B20_Init())
	 {
		 printf("error");
		 delay_ms(2000);
	 }
	 delay_ms(500);
	  while(1)
   {
  DHT11_Read_Data(&temperature,&humidity);//读取温湿度值    
		 delay_ms(500);
  Temp=DS18B20_Get_Temp();	
		if(Temp<0)
		{
			Temp=-Temp;
		}
		delay_ms(1000);
 delay_ms(1000);
  delay_ms(2000);
		 	printf("当前环境温度: %d ℃\r\n",temperature);    
      printf("当前环境湿度: %d %%\r\n",humidity); 
		printf("当前ds18b20读取温度 : %.2f ℃\r\n",Temp);
	 }
	/*LED_Init();		  		//3?ê??ˉó?LEDá??óμ?ó2?t?ó?ú
	LCD_Init();			   	//3?ê??ˉLCD  
 	POINT_COLOR=RED;		//éè??×?ì??aoìé? 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DHT11 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/16");		  
 	while(DHT11_Init())	//DHT113?ê??ˉ	
	{
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(30,130,200,16,16,"DHT11 OK");
	POINT_COLOR=BLUE;//éè??×?ì??aà?é? 
 	LCD_ShowString(30,150,200,16,16,"Temp:  C");	 
 	LCD_ShowString(30,170,200,16,16,"Humi:  %");	 
	while(1)
	{	    	    
 		if(t%10==0)			//??100ms?áè?ò?′?
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//?áè???êa?è?μ					    
			LCD_ShowNum(30+40,150,temperature,2,16);	//??ê????è	   		   
			LCD_ShowNum(30+40,170,humidity,2,16);		//??ê?êa?è	 	   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}*/
	
}




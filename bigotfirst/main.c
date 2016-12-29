#include <string.h>
#include <stdlib.h>
#include "stm32f10x.h"
//#include "bsp_gpio.h"
#include"usart.h"
#include   "usart2.h"
//#include "wifi_config.h"
//#include "wifi_function.h"
//#include "bsp_SysTick.h"
#include "delay.h"
#include "sys.h"
#include "dht11_.h"
#include "8266config.h"
#include "malloc.h"
#include "tempusart.h"
#include "bsp_ds18b20.h"
/*int main(void)
{
	u8 i;
//	u16 num=0;
//	char seat[30][2]={0};
//	char *symbol="[{";
//	char *address=NULL;
	// 初始化
	WiFi_RST_INIT();
    WiFi_USART1_INIT(); 
	WiFi_USART2_INIT(); 
	WiFi_NVIC_INIT();                                                                 
	SysTick_Init();//配置 SysTick 为 1ms 中断一次 
	                                                               
	PC_Usart ("\r\n 测试开始\r\n");                            //打印测试例程提示信息
	ESP8266_init();
	while(1)
	{
			Delay_ms(2000);
			Delay_ms(1000);
//			num++;
//			PC_Usart ("\r\n%d\r\n",num);
			Web_To_ESP();
			Delay_ms(500);
//			address=strstr(strEsp8266_Fram_Record .Data_RX_BUF,symbol);
//			parseJson_array(address,seat);
//			for(i=0;i<30;i++)	
//					PC_Usart ("%d",seat[i][1]);//逐个发送数据到串口1			
	}

}*/
 float tem;
float temp;
float  humi;
float Temp;
//uint16_t  huo;
int main(void)
{
		/*u8 *tempStr;       //字符串格式温度
    u8 *humiStr;       //字符串格式湿度
		u8 *huoStr;*/
	u8 *alldata;
  u8  n=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  mem_init();	
	uart_init(115200);
	 USART2_Init(115200);
	//TIM3_Int_Init(7199,9999);  //1s
	DHT11_Init();
	delay_ms(200);
	 T_Adc_Init();	
	delay_ms(200);
	DS18B20_Init();
	//delay_ms(200);
	printf("DHT11 and ADC init successfully");
	//ESP8266_init();  //此处不需要每一次都要进行初始化，在连接不上的时候再进行初始化。因为8266会自己连接WIFI。
	/*sprintf((char*)str,"{\"M\":\"update\",\"ID\":\"284\",\"V\":{\"";   //",bigiod_ID,(u8*)bigiod_apiKey)；
   str+="273\":\"";
	str+=temp;
	str+="\",\"274\":\""
	str+=heat; 
  str+="\",\"295\":\"";
   str+=huo; 
  // str+="\",\"323\":\"";
	str+="\"}}\n\n\n";*/
	
	//sprintf(str);
	//sprintf("temp:");
  //str+=temp;
	
	//sprintf((char*)str,"{\"M\":\"update\",\"ID\":\"284\",\"V\":{\"273":\"%s\",\"274":\"%s\",\"295":\"%s\"}",temp,hemi,huo);
	/*printf("{\"M\":\"update\",\"ID\":\"284\",\"V\":{\"273":\"%s\",\"274":\"%s\",\"295":\"%s\"}",temp,hemi,huo);
}  */

/*void ESP8266_task(void *pdata)
{	
  
  while(1)
  {
    ESP8266_search();
    
    delay_ms(100);
  }
 
}
void ESP8266_hold_task(void *pdata)
{	
  u8 *p;
  u8  n=0,k;
  ESP8266.DISCONNECT_T=1;          //?a?úè??aò??-ê§áa￡?éè??3?ê±×′ì???????á?￡?Dèòaè???á??óμ?2?Dèòa3?ê??ˉ?￡
  while(ESP8266_connect())       //?a?úá??óò?′?
  {
     delay_ms(3000);             //?óê±4???ú·??ê  
     if(ESP8266_check("checked")==0)   goto  AA16;	
     if((++n)==8)             goto  AA16;	       //?a?úá??ón′?2?3é1|￡?ì?3?
     for(k=0;k<5;k++) 
     {
       delay_ms(3000);            //?óê±4???ú·??ê  
       if(ESP8266_login()==0)  goto  AA16;	//??′?á??óò?′?μ???10′?￡?3é1|μ????íì?3?
       delay_ms(3000);             //?óê±4???ú·??ê  
       if(ESP8266_check("connected")==0)  k--;	
     }
  }
  AA16:
  delay_ms(4000);                //?óê±4???ú·??ê  
  while(1)
  {
    ESP8266_hold(); //?ú2??ˉ3é?óê±
    p=mymalloc(SRAMIN,40);							        //éê??32×??ú?ú′?
    //Get_Temprate();
		 DHT11_Read_Data(&temp,&humi);
    sprintf((char*)p,"{\"M\":\"update\",\"ID\":\"284\",\"V\":{\"273\":\"%.2f\",\"274\":\"295\"}}",chip_Temprate);//μ?????á?(float)chip_Temprate
    atk_8266_send_cmd(p,0,0);
    myfree(SRAMIN,p);  			//?ú′?êí·?(ía2?μ÷ó?)
  }
 
}
	*/

		//int len;
		delay_ms(5000);
  ESP8266.DISCONNECT_T=1;                                  //开机认为已经失联，设置超时状态强制重连，需要让其连接但不需要初始化。
  while(ESP8266_connect())                                 //开机连接一次
  {
     delay_ms(1000);                                      //延时4秒在访问  
     if(ESP8266_check("checked")==0)       goto  AA16;	
     delay_ms(1000); 
     while(1)  
     {
        if(ESP8266_login()==0)             goto  AA16;	
        if(ESP8266_check("checked")==0)    goto  AA16;	
        n++;                                   //延时
        if(n>20)   break;                      //超过20次默认退出登录，进行连接服务器操作
     }
  }
  AA16:
  delay_ms(2000);                //延时4秒在访问  
	while(1)
	{
		
		ESP8266_hold();
		/*tempStr=mymalloc(40);
		humiStr=mymalloc(40);
		huoStr=mymalloc(40);*/
		printf("ready\r\n");
		alldata=mymalloc(300);
		DHT11_Read_Data(&temp,&humi);
		delay_ms(2000);
		//delay_ms(300);
		 tem=Get_Temprate();
		delay_ms(2000);
		Temp=DS18B20_Get_Temp();	
		if(Temp<0)
		{
			Temp=-Temp;
		}
		delay_ms(1000);
		/*sprintf(tempStr,"%d",temp);
		sprintf(humiStr,"%d",humi);
		sprintf(huoStr,"%d",huo);*/
		sprintf((char*)alldata,"{\"M\":\"update\",\"ID\":\"284\",\"V\":{\"273\":\"%.2f\",\"274\":\"%.2f\",\"295\":\"%.2f\",\"337\":\"%.2f\"}}\n",temp,humi,tem,Temp);
		printf("update\r\n");
		/*atk_8266_send_cmd(tempStr,0,0);
    //myfree(tempStr);  
		atk_8266_send_cmd(humiStr,0,0);
		myfree(humiStr);  
		atk_8266_send_cmd(huoStr,0,0);
		myfree(huoStr);  */
		atk_8266_send_cmd(alldata,0,0);
		delay_ms(10);
		myfree(alldata);
	}
}
	
	

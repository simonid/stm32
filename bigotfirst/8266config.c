#include "8266config.h"
#include"usart.h"
//#include "HC74HC.h"
//#include "24cxx.h" 
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//ATK-ESP8266 WIFI模块 公用驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/4/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//用户配置区
/*const u8* reply0="无法识别的指令";	
const u8* reply1="屏幕已开";	
const u8* reply2="屏幕已关";	
const u8* reply3="灯已打开";	
const u8* reply4="灯已关闭";	
const u8* reply9="灯已打开10s";	
const u8* reply10="蜂鸣器开启1s";	*/
//用户配置区
//const u8* esp8266_="{\"M\":\"say\",\"ID\":\"U397\",\"C\":\"LED OK\\u6536\\u5230\\u6570\\u636e\",\"SIGN\":\"123\"}";			//路由器SSID号
const u8* esp8266_="{\"M\":\"say\",\"ID\":\"284\",\"C\":\"LED OK收到数据\",\"SIGN\":\"123\"}";			//路由器SSID号
//连接端口号:8086,可自行修改为其他端口.apiKey
_ESP8266 ESP8266; 		 

//连接端口号:8086,可自行修改为其他端口.apiKey
const u8* portnum="8085";		 

//bigiod_ip和端口
const u8* bigiod_ip="www.bigiot.net";			//路由器SSID号
const u8* bigiod_portnum="8181";	//wpa/wpa2 aes加密方式

//bigiod登录指令
const u8* bigiod_ID="284";	//wpa/wpa2 aes加密方式
const u8* bigiod_apiKey="fdcd5bc67";	//wpa/wpa2 aes加密方式


//WIFI STA模式,设置要去连接的路由器无线参数,请根据你自己的路由器设置,自行修改.
const u8* wifista_ssid="HQ203";			//路由器SSID号
const u8* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes加密方式
const u8* wifista_password="haiqian@203"; 	//连接密码

//WIFI AP模式,模块对外的无线参数,可自行修改.
const u8* wifiap_ssid="XYY-ESP8266";			//对外SSID号
const u8* wifiap_encryption="wpawpa2_aes";	//wpa/wpa2 aes加密方式
const u8* wifiap_password="12345678"; 		//连接密码 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//4个网络模式
const u8 *ATK_ESP8266_CWMODE_TBL[3]={"STA模式 ","AP模式 ","AP&STA模式 "};	//ATK-ESP8266,3种网络模式,默认为路由器(ROUTER)模式 
//4种工作模式
const u8 *ATK_ESP8266_WORKMODE_TBL[3]={"TCP服务器","TCP客户端"," UDP 模式"};	//ATK-ESP8266,4种工作模式
//5种加密方式
const u8 *ATK_ESP8266_ECN_TBL[5]={"OPEN","WEP","WPA_PSK","WPA2_PSK","WPA_WAP2_PSK"};
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//usmart支持部分
//将收到的AT指令应答数据返回给电脑串口
//mode:0,不清零USART2_RX_STA;
//     1,清零USART2_RX_STA;
void atk_8266_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		printf("%s\r\n\r\n",USART2_RX_BUF);	//发送到串口
		if(mode)USART2_RX_STA=0;
	} 
}
//ATK-ESP8266发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)
u8* atk_8266_check_cmd(u8 *str)
{
	
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//向ATK-ESP8266发送命令
//cmd:发送的命令字符串
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s\r\n",cmd);	//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(atk_8266_check_cmd(ack))
				{
					//printf("ack:%s\r\n",(u8*)ack);
					break;//得到有效数据 
				}
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//向ATK-ESP8266发送指定数据
//data:发送的数据(不需要添加回车了)
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)luojian
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s",data);	//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(atk_8266_check_cmd(ack))break;//得到有效数据 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
}
//ATK-ESP8266退出透传模式
//返回值:0,退出成功;
//       1,退出失败
u8 atk_8266_quit_trans(void)
{
	while((USART2->SR&0X40)==0);	//等待发送空
	USART2->DR='+';      
	delay_ms(15);					//大于串口组帧时间(10ms)
	while((USART2->SR&0X40)==0);	//等待发送空
	USART2->DR='+';      
	delay_ms(15);					//大于串口组帧时间(10ms)
	while((USART2->SR&0X40)==0);	//等待发送空
	USART2->DR='+';      
	delay_ms(500);					//等待500ms
	return atk_8266_send_cmd("AT","OK",20);//退出透传判断.
}
//获取ATK-ESP8266模块的AP+STA连接状态
//返回值:0，未连接;1,连接成功
u8 atk_8266_apsta_check(void)
{
	if(atk_8266_quit_trans())return 0;			//退出透传 
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//发送AT+CIPSTATUS指令,查询连接状态
	if(atk_8266_check_cmd("+CIPSTATUS:0")&&
		 atk_8266_check_cmd("+CIPSTATUS:1")&&
		 atk_8266_check_cmd("+CIPSTATUS:2")&&
		 atk_8266_check_cmd("+CIPSTATUS:4"))
		return 0;
	else return 1;
}
//获取ATK-ESP8266模块的连接状态
//返回值:0,未连接;1,连接成功.
u8 atk_8266_consta_check(void)
{
	u8 *p;
	u8 res;
	if(atk_8266_quit_trans())return 0;			//退出透传 
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//发送AT+CIPSTATUS指令,查询连接状态
	p=atk_8266_check_cmd("+CIPSTATUS:"); 
	res=*p;									//得到连接状态	
	return res;
}


u8 ESP8266_init(void)
{
	u8 *p,*wifi_ssid,*wifi_password;
  u8  k;
  wifi_ssid=mymalloc(50);							//申请32字节内存
  wifi_password=mymalloc(50);							//申请32字节内存
//  AT24CXX_Read(400,wifi_ssid,50);
//  AT24CXX_Read(450,wifi_password,50);

  
  ESP8266.wifista_ssid=(u8* )wifista_ssid;
  ESP8266.wifista_password=(u8* )wifista_password;
  
  //ESP8266.wifista_ssid=(u8* )wifi_ssid, ESP8266.wifista_password=(u8* )wifi_password;
	while(atk_8266_send_cmd("AT","OK",20))//检查WIFI模块是否在线
	{
		atk_8266_quit_trans();//退出透传
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //关闭透传模式	
	  delay_ms(10);
  } 
  while(atk_8266_send_cmd("ATE0","OK",20));//关闭回显
	p=mymalloc(32);							//申请32字节内存
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//设置WIFI STA模式
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP服务器关闭(仅AP模式有效) 
	delay_ms(3000);         //延时3S等待重启成功
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",ESP8266.wifista_ssid,ESP8266.wifista_password);//设置无线参数:ssid,密码
  //atk_8266_send_cmd(p,0,0);
	if(atk_8266_send_cmd(p,"WIFI DISCONNECT",500)==0)	return 1 ;				//连接目标路由器,并且获得IP//不成功，退出初始化
  delay_ms(1000);
  atk_8266_send_cmd("AT+CIPMUX=0","OK",200);   //0：单连接，1：多连接
  sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",bigiod_ip,(u8*)bigiod_portnum);    //配置目标TCP服务器
  while(atk_8266_send_cmd(p,"WELCOME TO BIGIOT",200))
  {
      if(atk_8266_send_cmd(p,"ALREADY CONNECTED",200)==0) break;//得到有效数据
      else return 1 ;                                           //不成功，退出初始化
  }  
  atk_8266_send_cmd("AT+CIPMODE=1","OK",20);      //传输模式为：透传			
  atk_8266_send_cmd("AT+CIPSEND",">",20);         //开始透传           
  delay_ms(500);
  k=0;//登录
  printf("登录\r\n");
  while(ESP8266_login())
  {
     k++;
     if(k>30) break;    
  }
  myfree(wifi_password); //释放32字节内存
  myfree(wifi_ssid); //释放32字节内存
  myfree(p); //释放32字节内存
  if(k) return 1 ;
  else  return 0 ;
}

//ATK-ESP8266初始化函数
u8 ESP8266_connect(void)
{
	u8 *ser;
  u8  k;
	while(atk_8266_send_cmd("AT","OK",20))//检查WIFI模块是否在线
	{
		atk_8266_quit_trans();//退出透传
	  delay_ms(10);
  } 
	ser=mymalloc(50);							        //申请32字节内存
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//设置WIFI STA模式
	atk_8266_send_cmd("AT+RST","OK",20);	    	//DHCP服务器关闭(仅AP模式有效) 
	delay_ms(2000);                             //延时3S等待重启成功
  sprintf((char*)ser,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)bigiod_ip,(u8*)bigiod_portnum);    //配置目标TCP服务器
  while(atk_8266_send_cmd(ser,"WELCOME TO BIGIOT",200))
  {
      if(atk_8266_send_cmd(ser,"ALREADY CONNECTED",200)==0) break;//得到有效数据
      if(atk_8266_send_cmd(ser,"no ip",100)==0)         //无IP，跳过连接到后面进行初始化。
      {
         ESP8266.enforce=5;            //无IP需要立即进行初始化操作，强制初始化
         return 0 ;
      }
  }  
  atk_8266_send_cmd("AT+CIPMODE=1","OK",20);      //传输模式为：透传			
  atk_8266_send_cmd("AT+CIPSEND",">",20);         //开始透传           
  delay_ms(500);
  k=0;//登录
  printf("登录\r\n");
  while(ESP8266_login())
  {
     k++;
     if(k>3) break;     //原本的值是30
  }
  myfree(ser); //释放32字节内存connected
  if(k) return 1 ;
  else  return 0 ;
}
//ATK-ESP8266初始化函数
u8 ESP8266_login(void)
{
	u8 *p,*str;
  u8  k;
  p=mymalloc(50);							        //申请32字节内存
	str=mymalloc(32);
  sprintf((char*)p,"{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}",bigiod_ID,(u8*)bigiod_apiKey);//登录指令
  sprintf((char*)str,"\"ID\":\"D%s\"",bigiod_ID);
	k=atk_8266_send_cmd(p,str,200);
  printf("登录\r\n");
  myfree(p); //释放32字节内存connected
	myfree(str);
 // if(k) return 1 ;
  //else  return 0 ;
	return k;
}
//ATK-ESP8266初始化函数
u8 ESP8266_check(u8* str)
{
  u8 k;
  k=atk_8266_send_cmd("{\"M\":\"status\"}",(u8*)str,200);//检测心跳
  if(k) return 1 ;
  else  return 0 ;
}


//ESP8266检查保持在线函数，单位S，内部已经延时45s，未登录内部循环10s。
void ESP8266_hold(void)
{
  u8 k;
  AA18:
  ESP8266.status=8;//默认有心跳
  
  k=ESP8266_check("checked");//检测心跳
  if(k==0)                             ESP8266.DISCONNECT_T=0;    //有心跳
  if((k!=0)&&(ESP8266.DISCONNECT_T==0))
  {
     ESP8266.DISCONNECT_T++;    //无心跳计时
     ESP8266.DISCONNECT_C++;    //掉线次数+1
  }
  
  if(ESP8266.DISCONNECT_T>60)          ESP8266.status=7;//无心跳需要重新登录
  if(ESP8266.DISCONNECT_T>300)         ESP8266.status=6;//无心跳需要重新连接
  if(ESP8266.DISCONNECT_T>600)         ESP8266.status=5;//无心跳需要重新初始化
  if(ESP8266.enforce)                  ESP8266.status=ESP8266.enforce;//强制选项条件
  if(ESP8266.enforce)                  ESP8266.DISCONNECT_T++;    //无心跳计时
  if(ESP8266.enforce)                  ESP8266.enforce=0;//强制选项条件清空
  //选择操作内容
  switch(ESP8266.status)
  {
    case 5: 
            while(ESP8266_init()) 
            {
              delay_ms(30000); 
              if(ESP8266_check("checked")==0) goto  AA18 ;//检测心跳
              delay_ms(30000); 
            }
            goto  AA18 ;	 
    case 6: 
            ESP8266_connect();// 超过300s重新连接服务器
            delay_ms(10000);
            goto  AA18 ;	 
    case 7: 
            if(ESP8266_login()==0)   ESP8266.status=8;//检查不在线，重新登录deng
            delay_ms(5000);
            break;	 
    case 8: 
            delay_ms(45000);
            break;	 
    default:
            break;	
  }
  if(ESP8266.status!=8)  
  {
     delay_ms(3000);
     goto  AA18 ;
  }
}


/*
//ESP8266接收数据后，对特定数据进行搜索?
//str:期待的应答结果
//返回值:0,返回相应的结果
// 其他,期待应答结果的位置(str的位置)
u16 ESP8266_search(void)
{
	u8 res=0,strN; 
	u8 *p,*p2,*strA,*strB,*reply;
  p=mymalloc(100);							        //申请100字节内存
  p2=mymalloc(100);							        //申请100字节内存
  if(USART2_RX_STA&0X8000)//接收到期待的应答结果
  {
    //判断指令类型
    if(atk_8266_check_cmd("\"M\":\"login\""))    res=login; //检查上线
    if(atk_8266_check_cmd("\"M\":\"logout\""))   res=logout; //检查下线
    if(atk_8266_check_cmd("\"M\":\"say\""))      res=say; //检查对话
    //跳转类型操作
    switch(res)
    {
      case login:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    ESP8266.xyy_web_login=1; //检查上线
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     ESP8266.xyy_wx_login=1; //检查上线
          if(atk_8266_check_cmd("\"guest\""))                ESP8266.guest_login=1; //检查上线
          break;	 
      case logout:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    ESP8266.xyy_web_logout=1; //检查下线
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     ESP8266.xyy_wx_logout=1; //检查下线
          if(atk_8266_check_cmd("\"guest\""))                ESP8266.guest_logout=1; //检查下线
          break;	 
      case say:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     res=xyy840948307wx;//检查下线
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    res=xyy840948307web; //检查下线
          if(atk_8266_check_cmd("\"guest\""))                res=guest; //检查下线
          res=1; //强制
          goto AA10; 
          
      default:
          res=0;
          break;	
    }
    goto AA20; //无命令，跳转到文末

    AA10://say对话操作
    reply=(u8*)reply0;
    switch(res)
    {
      case xyy840948307wx://微信对话,命令字符在“C” 和“T” 之间
          res=0;
          strA=atk_8266_check_cmd("\"C\"")+5   ; //检查命令字符第一个字符位置, 向右偏移5个字节
          strB=atk_8266_check_cmd("\"T\"")-3   ; //检查命令字符最后一个个字符位置, 向左偏移3个字节
          strN=strB-strA+1;                      //加1是防止最后一个字符丢失
          memcpy(p,strA,strN);                   //复制字符串
          p[strN]=0;                             //添加结束符
          order2str(p);
          printf("%s\r\n",(u8*) p);	//发送到串口  "\u52a0\u6cb9" 

          strN=0;
          if(strstr((const char*)p,(const char*)"开灯"))       strN=1;
          if(strstr((const char*)p,(const char*)"开灯1"))      strN=1;
          if(strstr((const char*)p,(const char*)"继电器开"))   strN=1;
          if(strN)                                             K0.DO=1,reply=(u8*)reply3;

          strN=0;
          if(strstr((const char*)p,(const char*)"关灯"))       strN=1;
          if(strstr((const char*)p,(const char*)"关灯1"))      strN=1;
          if(strstr((const char*)p,(const char*)"继电器关"))   strN=1;
          if(strN)                                             K0.DO=0,reply=(u8*)reply4;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"屏幕开"))     strN=1;
          if(strstr((const char*)p,(const char*)"up"))         strN=1;
          if(strN)                        LCD_ON,LCD_ONT=30000,reply=(u8*)reply1;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"屏幕关"))     strN=1;
          if(strstr((const char*)p,(const char*)"down"))       strN=1;
          if(strN)                                             LCD_OFF,reply=(u8*)reply2;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"喇叭"))       strN=1;
          if(strstr((const char*)p,(const char*)"蜂鸣器"))     strN=1;
          if(strstr((const char*)p,(const char*)"报警"))       strN=1;
          if(strN)                                             Beep_T=2000 ,reply=(u8*)reply10;
          
          if(strstr((const char*)p,(const char*)"offOn"))  K0.DO=!K0.DO, K0.TN=10000 ,reply=(u8*)reply9;
          if(strstr((const char*)p,(const char*)"play"))   Beep_T=1000 ,reply=(u8*)reply10;
          
          sprintf((char*)p2,"{\"M\":\"say\",\"ID\":\"284\",\"C\":\"%s\",\"SIGN\":\"123\"}",(char*)reply);
          str2order(p2);
          atk_8266_send_cmd((u8*)p2,0,0);
          break;	 
      case xyy840948307web://web对话
          res=0;
          break;	 
      case guest://guest对话 R??
          res=0;
          break;	 
      default:
          res=0;
          break;
    }
    AA20:
    USART2_RX_STA=0;
  } 
  myfree(p); //释放100字节内存
  myfree(p2); //释放100字节内存

  return 0;
}


void order2str(u8* str)
{
   u16 j=0,n=0,res;
   while(str[j]) //判断索检到末尾
   {
      if((str[j]=='\\')&&(str[j+1]=='u'))
      {
         if(str[j+2]<58) str[j+2]-=48;
         else            str[j+2]-=87;
         if(str[j+3]<58) str[j+3]-=48;
         else            str[j+3]-=87;
         if(str[j+4]<58) str[j+4]-=48;
         else            str[j+4]-=87;
         if(str[j+5]<58) str[j+5]-=48;
         else            str[j+5]-=87;
         str[n]=str[j+2]*16+str[j+3];
         str[n+1]=str[j+4]*16+str[j+5];
         res=(str[n]*256)+str[n+1];    //编码求和
         res=ff_convert(res,0);       //Converted code, 0 means conversion error
         if(res<0x0100) res=0x3f3f;    //汉字编码不能小于这个数
         str[n]=res>>8,str[n+1]=res;   //编码分解
         n+=2,j+=6;
      }else
      {
         str[n]=str[j];
         n++,j++;
      }
   }
   str[n]=0; //索检到末尾，添加结束符
}



//p；  j{"M":"say","ID":"U397","C":"LED OK收到数据","SIGN":"123"}
//str；n{"M":"say","ID":"U397","C":"LED OK\u6536\u5230\u6570\u636e","SIGN":"123"}
void str2order(u8* str)
{
   u16 j=0,n=0,res;
   u8 *p;
   p=mymalloc(100);							        //申请100字节内存
   strcpy((char*)p,(char*)str);
   while(p[j]) //判断索检到末尾
   {
      if((p[j]&0x80)>0)
      {  
         str[n]='\\';
         str[n+1]='u';
         n+=2;
        
         res=(p[j]*256)+p[j+1];
         res=ff_convert(res,1);        // Converted code, 0 means conversion error 
         p[j]=res>>8,p[j+1]=res;
        
         str[n]=p[j]>>4,str[n+1]=p[j]&0x0f;
         str[n+2]=p[j+1]>>4,str[n+3]=p[j+1]&0x0f;
        
         if(str[n]<10)   str[n]+=48;
         else            str[n]+=87;
         if(str[n+1]<10) str[n+1]+=48;
         else            str[n+1]+=87;
         if(str[n+2]<10) str[n+2]+=48;
         else            str[n+2]+=87;
         if(str[n+3]<10) str[n+3]+=48;
         else            str[n+3]+=87;
        
         n+=4,j+=2;
      }else
      {
         str[n]=p[j];
         n++,j++;
      }
   }
   str[n]=0; //索检到末尾，添加结束符
   myfree(p); //释放100字节内存

}

*/



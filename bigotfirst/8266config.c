#include "8266config.h"
#include"usart.h"
//#include "HC74HC.h"
//#include "24cxx.h" 
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� ������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//�û�������
/*const u8* reply0="�޷�ʶ���ָ��";	
const u8* reply1="��Ļ�ѿ�";	
const u8* reply2="��Ļ�ѹ�";	
const u8* reply3="���Ѵ�";	
const u8* reply4="���ѹر�";	
const u8* reply9="���Ѵ�10s";	
const u8* reply10="����������1s";	*/
//�û�������
//const u8* esp8266_="{\"M\":\"say\",\"ID\":\"U397\",\"C\":\"LED OK\\u6536\\u5230\\u6570\\u636e\",\"SIGN\":\"123\"}";			//·����SSID��
const u8* esp8266_="{\"M\":\"say\",\"ID\":\"284\",\"C\":\"LED OK�յ�����\",\"SIGN\":\"123\"}";			//·����SSID��
//���Ӷ˿ں�:8086,�������޸�Ϊ�����˿�.apiKey
_ESP8266 ESP8266; 		 

//���Ӷ˿ں�:8086,�������޸�Ϊ�����˿�.apiKey
const u8* portnum="8085";		 

//bigiod_ip�Ͷ˿�
const u8* bigiod_ip="www.bigiot.net";			//·����SSID��
const u8* bigiod_portnum="8181";	//wpa/wpa2 aes���ܷ�ʽ

//bigiod��¼ָ��
const u8* bigiod_ID="284";	//wpa/wpa2 aes���ܷ�ʽ
const u8* bigiod_apiKey="fdcd5bc67";	//wpa/wpa2 aes���ܷ�ʽ


//WIFI STAģʽ,����Ҫȥ���ӵ�·�������߲���,��������Լ���·��������,�����޸�.
const u8* wifista_ssid="HQ203";			//·����SSID��
const u8* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const u8* wifista_password="haiqian@203"; 	//��������

//WIFI APģʽ,ģ���������߲���,�������޸�.
const u8* wifiap_ssid="XYY-ESP8266";			//����SSID��
const u8* wifiap_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const u8* wifiap_password="12345678"; 		//�������� 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//4������ģʽ
const u8 *ATK_ESP8266_CWMODE_TBL[3]={"STAģʽ ","APģʽ ","AP&STAģʽ "};	//ATK-ESP8266,3������ģʽ,Ĭ��Ϊ·����(ROUTER)ģʽ 
//4�ֹ���ģʽ
const u8 *ATK_ESP8266_WORKMODE_TBL[3]={"TCP������","TCP�ͻ���"," UDP ģʽ"};	//ATK-ESP8266,4�ֹ���ģʽ
//5�ּ��ܷ�ʽ
const u8 *ATK_ESP8266_ECN_TBL[5]={"OPEN","WEP","WPA_PSK","WPA2_PSK","WPA_WAP2_PSK"};
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//usmart֧�ֲ���
//���յ���ATָ��Ӧ�����ݷ��ظ����Դ���
//mode:0,������USART2_RX_STA;
//     1,����USART2_RX_STA;
void atk_8266_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		printf("%s\r\n\r\n",USART2_RX_BUF);	//���͵�����
		if(mode)USART2_RX_STA=0;
	} 
}
//ATK-ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* atk_8266_check_cmd(u8 *str)
{
	
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//��ATK-ESP8266��������
//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s\r\n",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))
				{
					//printf("ack:%s\r\n",(u8*)ack);
					break;//�õ���Ч���� 
				}
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//��ATK-ESP8266����ָ������
//data:���͵�����(����Ҫ��ӻس���)
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)luojian
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s",data);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))break;//�õ���Ч���� 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
}
//ATK-ESP8266�˳�͸��ģʽ
//����ֵ:0,�˳��ɹ�;
//       1,�˳�ʧ��
u8 atk_8266_quit_trans(void)
{
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	delay_ms(500);					//�ȴ�500ms
	return atk_8266_send_cmd("AT","OK",20);//�˳�͸���ж�.
}
//��ȡATK-ESP8266ģ���AP+STA����״̬
//����ֵ:0��δ����;1,���ӳɹ�
u8 atk_8266_apsta_check(void)
{
	if(atk_8266_quit_trans())return 0;			//�˳�͸�� 
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//����AT+CIPSTATUSָ��,��ѯ����״̬
	if(atk_8266_check_cmd("+CIPSTATUS:0")&&
		 atk_8266_check_cmd("+CIPSTATUS:1")&&
		 atk_8266_check_cmd("+CIPSTATUS:2")&&
		 atk_8266_check_cmd("+CIPSTATUS:4"))
		return 0;
	else return 1;
}
//��ȡATK-ESP8266ģ�������״̬
//����ֵ:0,δ����;1,���ӳɹ�.
u8 atk_8266_consta_check(void)
{
	u8 *p;
	u8 res;
	if(atk_8266_quit_trans())return 0;			//�˳�͸�� 
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//����AT+CIPSTATUSָ��,��ѯ����״̬
	p=atk_8266_check_cmd("+CIPSTATUS:"); 
	res=*p;									//�õ�����״̬	
	return res;
}


u8 ESP8266_init(void)
{
	u8 *p,*wifi_ssid,*wifi_password;
  u8  k;
  wifi_ssid=mymalloc(50);							//����32�ֽ��ڴ�
  wifi_password=mymalloc(50);							//����32�ֽ��ڴ�
//  AT24CXX_Read(400,wifi_ssid,50);
//  AT24CXX_Read(450,wifi_password,50);

  
  ESP8266.wifista_ssid=(u8* )wifista_ssid;
  ESP8266.wifista_password=(u8* )wifista_password;
  
  //ESP8266.wifista_ssid=(u8* )wifi_ssid, ESP8266.wifista_password=(u8* )wifi_password;
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
		atk_8266_quit_trans();//�˳�͸��
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //�ر�͸��ģʽ	
	  delay_ms(10);
  } 
  while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
	p=mymalloc(32);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(3000);         //��ʱ3S�ȴ������ɹ�
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",ESP8266.wifista_ssid,ESP8266.wifista_password);//�������߲���:ssid,����
  //atk_8266_send_cmd(p,0,0);
	if(atk_8266_send_cmd(p,"WIFI DISCONNECT",500)==0)	return 1 ;				//����Ŀ��·����,���һ��IP//���ɹ����˳���ʼ��
  delay_ms(1000);
  atk_8266_send_cmd("AT+CIPMUX=0","OK",200);   //0�������ӣ�1��������
  sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",bigiod_ip,(u8*)bigiod_portnum);    //����Ŀ��TCP������
  while(atk_8266_send_cmd(p,"WELCOME TO BIGIOT",200))
  {
      if(atk_8266_send_cmd(p,"ALREADY CONNECTED",200)==0) break;//�õ���Ч����
      else return 1 ;                                           //���ɹ����˳���ʼ��
  }  
  atk_8266_send_cmd("AT+CIPMODE=1","OK",20);      //����ģʽΪ��͸��			
  atk_8266_send_cmd("AT+CIPSEND",">",20);         //��ʼ͸��           
  delay_ms(500);
  k=0;//��¼
  printf("��¼\r\n");
  while(ESP8266_login())
  {
     k++;
     if(k>30) break;    
  }
  myfree(wifi_password); //�ͷ�32�ֽ��ڴ�
  myfree(wifi_ssid); //�ͷ�32�ֽ��ڴ�
  myfree(p); //�ͷ�32�ֽ��ڴ�
  if(k) return 1 ;
  else  return 0 ;
}

//ATK-ESP8266��ʼ������
u8 ESP8266_connect(void)
{
	u8 *ser;
  u8  k;
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
		atk_8266_quit_trans();//�˳�͸��
	  delay_ms(10);
  } 
	ser=mymalloc(50);							        //����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","OK",20);	    	//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(2000);                             //��ʱ3S�ȴ������ɹ�
  sprintf((char*)ser,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)bigiod_ip,(u8*)bigiod_portnum);    //����Ŀ��TCP������
  while(atk_8266_send_cmd(ser,"WELCOME TO BIGIOT",200))
  {
      if(atk_8266_send_cmd(ser,"ALREADY CONNECTED",200)==0) break;//�õ���Ч����
      if(atk_8266_send_cmd(ser,"no ip",100)==0)         //��IP���������ӵ�������г�ʼ����
      {
         ESP8266.enforce=5;            //��IP��Ҫ�������г�ʼ��������ǿ�Ƴ�ʼ��
         return 0 ;
      }
  }  
  atk_8266_send_cmd("AT+CIPMODE=1","OK",20);      //����ģʽΪ��͸��			
  atk_8266_send_cmd("AT+CIPSEND",">",20);         //��ʼ͸��           
  delay_ms(500);
  k=0;//��¼
  printf("��¼\r\n");
  while(ESP8266_login())
  {
     k++;
     if(k>3) break;     //ԭ����ֵ��30
  }
  myfree(ser); //�ͷ�32�ֽ��ڴ�connected
  if(k) return 1 ;
  else  return 0 ;
}
//ATK-ESP8266��ʼ������
u8 ESP8266_login(void)
{
	u8 *p,*str;
  u8  k;
  p=mymalloc(50);							        //����32�ֽ��ڴ�
	str=mymalloc(32);
  sprintf((char*)p,"{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}",bigiod_ID,(u8*)bigiod_apiKey);//��¼ָ��
  sprintf((char*)str,"\"ID\":\"D%s\"",bigiod_ID);
	k=atk_8266_send_cmd(p,str,200);
  printf("��¼\r\n");
  myfree(p); //�ͷ�32�ֽ��ڴ�connected
	myfree(str);
 // if(k) return 1 ;
  //else  return 0 ;
	return k;
}
//ATK-ESP8266��ʼ������
u8 ESP8266_check(u8* str)
{
  u8 k;
  k=atk_8266_send_cmd("{\"M\":\"status\"}",(u8*)str,200);//�������
  if(k) return 1 ;
  else  return 0 ;
}


//ESP8266��鱣�����ߺ�������λS���ڲ��Ѿ���ʱ45s��δ��¼�ڲ�ѭ��10s��
void ESP8266_hold(void)
{
  u8 k;
  AA18:
  ESP8266.status=8;//Ĭ��������
  
  k=ESP8266_check("checked");//�������
  if(k==0)                             ESP8266.DISCONNECT_T=0;    //������
  if((k!=0)&&(ESP8266.DISCONNECT_T==0))
  {
     ESP8266.DISCONNECT_T++;    //��������ʱ
     ESP8266.DISCONNECT_C++;    //���ߴ���+1
  }
  
  if(ESP8266.DISCONNECT_T>60)          ESP8266.status=7;//��������Ҫ���µ�¼
  if(ESP8266.DISCONNECT_T>300)         ESP8266.status=6;//��������Ҫ��������
  if(ESP8266.DISCONNECT_T>600)         ESP8266.status=5;//��������Ҫ���³�ʼ��
  if(ESP8266.enforce)                  ESP8266.status=ESP8266.enforce;//ǿ��ѡ������
  if(ESP8266.enforce)                  ESP8266.DISCONNECT_T++;    //��������ʱ
  if(ESP8266.enforce)                  ESP8266.enforce=0;//ǿ��ѡ���������
  //ѡ���������
  switch(ESP8266.status)
  {
    case 5: 
            while(ESP8266_init()) 
            {
              delay_ms(30000); 
              if(ESP8266_check("checked")==0) goto  AA18 ;//�������
              delay_ms(30000); 
            }
            goto  AA18 ;	 
    case 6: 
            ESP8266_connect();// ����300s�������ӷ�����
            delay_ms(10000);
            goto  AA18 ;	 
    case 7: 
            if(ESP8266_login()==0)   ESP8266.status=8;//��鲻���ߣ����µ�¼deng
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
//ESP8266�������ݺ󣬶��ض����ݽ�������?
//str:�ڴ���Ӧ����
//����ֵ:0,������Ӧ�Ľ��
// ����,�ڴ�Ӧ������λ��(str��λ��)
u16 ESP8266_search(void)
{
	u8 res=0,strN; 
	u8 *p,*p2,*strA,*strB,*reply;
  p=mymalloc(100);							        //����100�ֽ��ڴ�
  p2=mymalloc(100);							        //����100�ֽ��ڴ�
  if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
  {
    //�ж�ָ������
    if(atk_8266_check_cmd("\"M\":\"login\""))    res=login; //�������
    if(atk_8266_check_cmd("\"M\":\"logout\""))   res=logout; //�������
    if(atk_8266_check_cmd("\"M\":\"say\""))      res=say; //���Ի�
    //��ת���Ͳ���
    switch(res)
    {
      case login:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    ESP8266.xyy_web_login=1; //�������
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     ESP8266.xyy_wx_login=1; //�������
          if(atk_8266_check_cmd("\"guest\""))                ESP8266.guest_login=1; //�������
          break;	 
      case logout:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    ESP8266.xyy_web_logout=1; //�������
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     ESP8266.xyy_wx_logout=1; //�������
          if(atk_8266_check_cmd("\"guest\""))                ESP8266.guest_logout=1; //�������
          break;	 
      case say:
          res=0;
          if(atk_8266_check_cmd("\"xyy840948307(wx)\""))     res=xyy840948307wx;//�������
          if(atk_8266_check_cmd("\"xyy840948307(web)\""))    res=xyy840948307web; //�������
          if(atk_8266_check_cmd("\"guest\""))                res=guest; //�������
          res=1; //ǿ��
          goto AA10; 
          
      default:
          res=0;
          break;	
    }
    goto AA20; //�������ת����ĩ

    AA10://say�Ի�����
    reply=(u8*)reply0;
    switch(res)
    {
      case xyy840948307wx://΢�ŶԻ�,�����ַ��ڡ�C�� �͡�T�� ֮��
          res=0;
          strA=atk_8266_check_cmd("\"C\"")+5   ; //��������ַ���һ���ַ�λ��, ����ƫ��5���ֽ�
          strB=atk_8266_check_cmd("\"T\"")-3   ; //��������ַ����һ�����ַ�λ��, ����ƫ��3���ֽ�
          strN=strB-strA+1;                      //��1�Ƿ�ֹ���һ���ַ���ʧ
          memcpy(p,strA,strN);                   //�����ַ���
          p[strN]=0;                             //��ӽ�����
          order2str(p);
          printf("%s\r\n",(u8*) p);	//���͵�����  "\u52a0\u6cb9" 

          strN=0;
          if(strstr((const char*)p,(const char*)"����"))       strN=1;
          if(strstr((const char*)p,(const char*)"����1"))      strN=1;
          if(strstr((const char*)p,(const char*)"�̵�����"))   strN=1;
          if(strN)                                             K0.DO=1,reply=(u8*)reply3;

          strN=0;
          if(strstr((const char*)p,(const char*)"�ص�"))       strN=1;
          if(strstr((const char*)p,(const char*)"�ص�1"))      strN=1;
          if(strstr((const char*)p,(const char*)"�̵�����"))   strN=1;
          if(strN)                                             K0.DO=0,reply=(u8*)reply4;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"��Ļ��"))     strN=1;
          if(strstr((const char*)p,(const char*)"up"))         strN=1;
          if(strN)                        LCD_ON,LCD_ONT=30000,reply=(u8*)reply1;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"��Ļ��"))     strN=1;
          if(strstr((const char*)p,(const char*)"down"))       strN=1;
          if(strN)                                             LCD_OFF,reply=(u8*)reply2;
          
          strN=0;
          if(strstr((const char*)p,(const char*)"����"))       strN=1;
          if(strstr((const char*)p,(const char*)"������"))     strN=1;
          if(strstr((const char*)p,(const char*)"����"))       strN=1;
          if(strN)                                             Beep_T=2000 ,reply=(u8*)reply10;
          
          if(strstr((const char*)p,(const char*)"offOn"))  K0.DO=!K0.DO, K0.TN=10000 ,reply=(u8*)reply9;
          if(strstr((const char*)p,(const char*)"play"))   Beep_T=1000 ,reply=(u8*)reply10;
          
          sprintf((char*)p2,"{\"M\":\"say\",\"ID\":\"284\",\"C\":\"%s\",\"SIGN\":\"123\"}",(char*)reply);
          str2order(p2);
          atk_8266_send_cmd((u8*)p2,0,0);
          break;	 
      case xyy840948307web://web�Ի�
          res=0;
          break;	 
      case guest://guest�Ի� R??
          res=0;
          break;	 
      default:
          res=0;
          break;
    }
    AA20:
    USART2_RX_STA=0;
  } 
  myfree(p); //�ͷ�100�ֽ��ڴ�
  myfree(p2); //�ͷ�100�ֽ��ڴ�

  return 0;
}


void order2str(u8* str)
{
   u16 j=0,n=0,res;
   while(str[j]) //�ж����쵽ĩβ
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
         res=(str[n]*256)+str[n+1];    //�������
         res=ff_convert(res,0);       //Converted code, 0 means conversion error
         if(res<0x0100) res=0x3f3f;    //���ֱ��벻��С�������
         str[n]=res>>8,str[n+1]=res;   //����ֽ�
         n+=2,j+=6;
      }else
      {
         str[n]=str[j];
         n++,j++;
      }
   }
   str[n]=0; //���쵽ĩβ����ӽ�����
}



//p��  j{"M":"say","ID":"U397","C":"LED OK�յ�����","SIGN":"123"}
//str��n{"M":"say","ID":"U397","C":"LED OK\u6536\u5230\u6570\u636e","SIGN":"123"}
void str2order(u8* str)
{
   u16 j=0,n=0,res;
   u8 *p;
   p=mymalloc(100);							        //����100�ֽ��ڴ�
   strcpy((char*)p,(char*)str);
   while(p[j]) //�ж����쵽ĩβ
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
   str[n]=0; //���쵽ĩβ����ӽ�����
   myfree(p); //�ͷ�100�ֽ��ڴ�

}

*/



#ifndef __COMMON_H__
#define __COMMON_H__	 
#include "sys.h"
//#include "usart.h"		
#include "delay.h"	
//#include "led.h"   	 
//#include "key.h"	 	 	 	 	 
//#include "lcd.h"   
//#include "w25qxx.h" 	 
//#include "touch.h" 	 
#include "malloc.h"
#include "string.h"    
//#include "text.h"		
#include "usart2.h" 
//#include "ff.h"
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
#define login    1	//  
#define logout   2	//  	 
#define say      3	//  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
#define xyy840948307wx    1	//  
#define xyy840948307web   2	//  	 
#define guest               3	//  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
#define login    1	//  
#define logout   2	//  	 
#define say      3	//  
//-----------------ESP8266������
typedef struct  
{										    
  u8    status;
  u8    enforce;
  u8    xyy_wx_login;
  u8    xyy_wx_logout;
  u8    xyy_web_login;
  u8    xyy_web_logout;
  u8    guest_login;
  u8    guest_logout;
  u16   DISCONNECT_T;
  u16   CONNECT_T;
  u16   DISCONNECT_C;
  u8*   wifista_ssid;
  u8*   wifista_password;
	u16   xyyDATA;		     //xyy
} _ESP8266; 	  
extern _ESP8266 ESP8266; 	

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
u8 ESP8266_init(void);//��ʼ������
u8 ESP8266_connect(void);
u8 ESP8266_login(void);
u8 ESP8266_check(u8* str);

void ESP8266_hold(void);
//u16  ESP8266_search(void);
//void order2str(u8* str);
//void str2order(u8* str);


u8 atk_8266_mode_cofig(u8 netpro);
void atk_8266_at_response(u8 mode);
u8* atk_8266_check_cmd(u8 *str);
u8 atk_8266_apsta_check(void);
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime);
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 atk_8266_quit_trans(void);
u8 atk_8266_consta_check(void);
void atk_8266_load_keyboard(u16 x,u16 y);
void atk_8266_key_staset(u16 x,u16 y,u8 keyx,u8 sta);
u8 atk_8266_get_keynum(u16 x,u16 y);
void atk_8266_get_wanip(u8* ipbuf);
void atk_8266_get_ip(u8 x,u8 y);
void atk_8266_msg_show(u16 x,u16 y,u8 wanip);
void atk_8266_wificonf_show(u16 x,u16 y,u8* rmd,u8* ssid,u8* encryption,u8* password);
u8 atk_8266_netpro_sel(u16 x,u16 y,u8* name);
void atk_8266_mtest_ui(u16 x,u16 y);

u8 atk_8266_ip_set(u8* title,u8* mode,u8* port,u8* ip);
void atk_8266_test(void);



u8 atk_8266_apsta_test(void);	//WIFI AP+STAģʽ����
u8 atk_8266_wifista_test(void);	//WIFI STA����
u8 atk_8266_wifiap_test(void);	//WIFI AP����

//�û����ò���
extern const u8* portnum;			//���Ӷ˿�
 
extern const u8* wifista_ssid;		//WIFI STA SSID
extern const u8* wifista_encryption;//WIFI STA ���ܷ�ʽ
extern const u8* wifista_password; 	//WIFI STA ����

extern const u8* wifiap_ssid;		//WIFI AP SSID
extern const u8* wifiap_encryption;	//WIFI AP ���ܷ�ʽ
extern const u8* wifiap_password; 	//WIFI AP ����

extern u8* kbd_fn_tbl[2];
extern const u8* ATK_ESP8266_CWMODE_TBL[3];
extern const u8* ATK_ESP8266_WORKMODE_TBL[3];
extern const u8* ATK_ESP8266_ECN_TBL[5];
#endif

















//const u8* esp8266_="{\"M\":\"say\",\"ID\":\"U397\",\"C\":\"�յ�����\",\"SIGN\":\"123\"}";			//·����SSID��

#include "sys.h"
#include "usart3.h"	
#include "led.h"  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART3_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); 
//    USART_SendData(USART3,(uint8_t)ch);   
//	return ch;
//}
//#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART3_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART3_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率

void usart3_init(u32 bound){
    //GPIO绔彛璁剧疆
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 //pb10 pb11
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//USART1_TX //璇/O鍦ㄤ笉琚玌SART椹卞姩鏃讹紝蹇呴』閰嶇疆鎴愭偓绌鸿緭鍏�(鎴栧紑婕忕殑杈撳嚭楂�)IN_FLOATING锛堝師 澶嶇敤鎺ㄦ尳杈撳嚭锛�   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;	
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //USART1_RX	 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//娴┖杈撳叆
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);
   //Usart3 NVIC 閰嶇疆

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//鎶㈠崰浼樺厛绾�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//瀛愪紭鍏堢骇3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ閫氶亾浣胯兘
	NVIC_Init(&NVIC_InitStructure);	//鏍规嵁鎸囧畾鐨勫弬鏁板垵濮嬪寲VIC瀵勫瓨鍣�
  
   //USART 鍒濆鍖栬缃�

	USART_InitStructure.USART_BaudRate = bound;//涓�鑸缃负9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//瀛楅暱涓�8浣嶆暟鎹牸寮�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//涓�涓仠姝綅
	USART_InitStructure.USART_Parity = USART_Parity_No;//鏃犲鍋舵牎楠屼綅
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//鏃犵‖浠舵暟鎹祦鎺у埗
	USART_InitStructure.USART_Mode =USART_Mode_Rx | USART_Mode_Tx;	//鏀跺彂妯″紡
	
    USART_Init(USART3, &USART_InitStructure); //鍒濆鍖栦覆鍙�
	//USART_HalfDuplexCmd(USART3, ENABLE);		//鍗婂弻宸ユā寮�
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//寮�鍚腑鏂�
    USART_Cmd(USART3, ENABLE);                    //浣胯兘涓插彛 
	/* 	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);           //浣胯兘涓插彛1鐨凞MA鍙戦��  
		MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)Sendbuff,2);//DMA1閫氶亾4,澶栬涓轰覆鍙�1,瀛樺偍鍣ㄤ负SendBuff,闀垮害5200.
		DMA_Cmd(DMA1_Channel4, ENABLE);  */
}

u16 ARMED=0;
void USART3_IRQHandler(void)                	//涓插彛1涓柇鏈嶅姟绋嬪簭
{
//	LED0=0;
	{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //鎺ユ敹涓柇(鎺ユ敹鍒扮殑鏁版嵁蹇呴』鏄�0x0d 0x0a缁撳熬)
		{
		Res =USART_ReceiveData(USART3);//(USART1->DR);	//璇诲彇鎺ユ敹鍒扮殑鏁版嵁
		
		if((USART3_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART3_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)
					USART3_RX_STA=0;//接收错误,重新开始
				else{ 
					USART3_RX_STA|=0x8000;	//接收完成了
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res;
					flag_change();
					}
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)
					USART3_RX_STA|=0x4000;
				else
					{
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
					USART3_RX_STA++;
						if(USART3_RX_STA>(USART_REC_LEN-1))
							USART3_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     	} 
	} 

#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 
#endif	
void Send_turn3(u8 ch)
{
	USART3->DR=(u8)ch ;
	while((USART3->SR&0X40)==0);//等待发送结束				
}
void flag_change(void)
{
	if((USART3_RX_BUF[0]=='A')&&(USART3_RX_BUF[1]=='T'))
	{
		if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='0')){State=ON;}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='1')){State=OFF;}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='2')){}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='3')){}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='4')){}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='5')){}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='6')){}			
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='7')){}			
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='8')){}
		else if((USART3_RX_BUF[2]=='0')&&(USART3_RX_BUF[3]=='9')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='0')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='1')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='2')){}			
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='3')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='4')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='5')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='6')){}			
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='7')){}			
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='8')){}
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='9')){}			
		else if((USART3_RX_BUF[2]=='1')&&(USART3_RX_BUF[3]=='0')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='2')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='2')){}			
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='3')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='4')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='5')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='6')){}			
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='7')){}			
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='8')){}
		else if((USART3_RX_BUF[2]=='2')&&(USART3_RX_BUF[3]=='9')){}	
	}
}

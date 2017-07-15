#include "stm32f10x.h"
#include "sys.h"
#include "action.h"
extern uint8_t Ov7725_vsync;
char result=4;
u8 go_flag=0;
u8 danger=0;
u8 i=0;
u8 distance;
u8 zhangai_flag=0;
u8 flag=0;
void jiance(void);
void jiance0(void);
void jiance1(void);
void jiance2(void);
void ceshi(void);

//whole
void go_ahead_left();
void go_ahead_right();
void xiao_go_ahead_left();
void xiao_go_ahead_right();
void xiao_leftturn();
void xiao_rightturn();
void x_left();
void x_right();
void big_rightturn();
void big_leftturn();
void kuazhang(void);
void g_xiao_rightturn(void);
void g_xiao_leftturn(void);
void jiance0_1(void);
void hand_move1(void);
void hand_move2(void);
void PWM_OUTPUT(void);
int main(void)
{	
	unsigned char i=0;
	usart1_init(72,9600);
	/* 液晶初始化 */
	LCD_Init();	
  //while(1);
  //#if 1
	/* ov7725 gpio 初始化 */
	Ov7725_GPIO_Config();	
	/* ov7725 寄存器配置初始化 */
	while(Ov7725_Init() != SUCCESS);	
	delay_init();
	NVIC_Configuration();
	uart5_init(1000000);				//与舵机通信
	arm_init();	
	VSYNC_Init();	
	Ov7725_vsync = 0;
	go_flag=0;
	Key_GPIO_Config();
//	LED_GPIO_Config();
//	TIM3_GPIO_Config();
	PWM_OUTPUT();
	while(1)
	{		
zhili();
jiance0_1();
delay_ms(1000);
jiance0_1();
delay_ms(1000);
		

l_first_tai0();
l_first_tai1();
l_mai();
l_luo0();
l_luo1();
r_tai0();
r_tai1();
r_mai();
r_luo0();
r_luo1();
l_second_tai0();
l_second_tai1();
//开始走一步	

l_mai();
l_luo0();
l_luo1();
r_tai0();
r_tai1();
r_mai();
r_luo0();
r_luo1();
l_second_tai0();
l_second_tai1();
//2
l_mai();
l_luo0();
l_luo1();
r_tai0();
r_tai1();
r_mai();
r_luo0();
r_luo1();
jiance0();
l_second_tai0();
l_second_tai1();
//for(i = 0; i>=5;i++)
//{
//l_mai();
//l_luo0();
//l_luo1();
//r_tai0();
//r_tai1();
//r_mai();
//r_luo0();
//r_luo1();
//l_second_tai0();
//l_second_tai1();
//}
go_flag=0;

while(1)
{	//go_flag       left=0  right=1
	if((result==1 || result == 2)&&danger==0)//  1左拐
	{
		hand_move1(); 
		printf("1122\r\n");
		if(zhangai_flag == 1)				
		{ 
			       
				printf("you left_turn\r\n");
				if(go_flag==1)  
				{
					xiaor_mai();
					xiaor_luo0();
					xiaor_luo1();	
					xiaol_tai0();
					xiaol_tai1();
        }
				g_xiao_leftturn(); 
		
    }		
    else 	
	  { 
			printf("wu left_turn\r\n");
			if(go_flag==1) 
			{
				r_mai();
				r_luo0();
				r_luo1();	
				l_second_tai0();
				l_second_tai1();
			}   
			xiao_leftturn();
	  }
		hand_move2();
  }
  if(result==3&&danger==0) //直行
	{
		hand_move1();
		 printf("3333\r\n");
		if(zhangai_flag==1)
		{		
			
			printf("you go_ahead\r\n");
			if(go_flag==0)  xiao_go_ahead_left();
			else            xiao_go_ahead_right();  
		}
		else
		{
			
			printf("wu go_ahead\r\n");
			if(go_flag==0)  go_ahead_left();
		  else             go_ahead_right();  
		}	
		hand_move2();
	}
	if((result==4 || result == 5)&&danger==0)   //4 右拐  
	{
		hand_move1();
		printf("4455\r\n");
    if( zhangai_flag== 1)				
		{
			hand_move1();
			printf("you right_turn\r\n");
			if(go_flag==0)  
			{
				xiaol_mai();
				xiaol_luo0();
				xiaol_luo1();	
				xiaol_luo2();
				xiaor_tai0();
				xiaor_tai1();
      }
      g_xiao_rightturn();         
    }		
		else
		{
			hand_move2();
			if(go_flag==0) 
			{
				printf("wu right_turn\r\n");
				l_mai();
				l_luo0();
				l_luo1();	
				r_tai0();
				r_tai1();
			}   
			big_rightturn();
		}
		hand_move2();
	}
	if(danger==1)
	{
			if(go_flag==0)  xiao_go_ahead_left();
			else            xiao_go_ahead_right();  

	}
	
}
}
}
 
void jiance0_1(void)          //wu zhang ai
{
	if( Ov7725_vsync == 2 )
	{
		FIFO_PREPARE;  			/*FIFO准备*/					
		biaozhun();		/*采集并显示*/
		Ov7725_vsync = 0;			
	}
}

void jiance0(void)          //wu zhang ai
{
	 printf("jiance0 wu_zhang_ai   ");
	if( Ov7725_vsync == 2 )
	{
		FIFO_PREPARE;  			/*FIFO准备*/					
		result=biaozhun();		/*采集并显示*/
		printf("result_wu = %d ", result);
		Ov7725_vsync = 0;			
	}
}
void jiance1(void)    //distance
{
	printf("jiance1_distance   ");
	if( Ov7725_vsync == 2 )
	{
		FIFO_PREPARE;  			/*FIFO准备*/					
		distance=getdistance();					/*采集并显示*/
		Ov7725_vsync = 0;			
		
		if(distance<110)  danger=1;
		else              danger=0;
		
		if(75<distance&&distance<240) zhangai_flag=1;
		else if(distance>=240)        zhangai_flag=0;
		else  if(distance <= 75	)    kuazhang();
		
		printf("distance=%d   ",distance);
		printf("zhangai_flag=%d\r\n",zhangai_flag);
	}
}
void jiance2(void)     //zhang ai turn
{
	 printf("jiance2 zhang ai   ");
	if( Ov7725_vsync == 2 )
	{ 
		FIFO_PREPARE;  			/*FIFO准备*/					
		result=ready_to();		//jiaodu 	/*采集并显示*/
		printf("result_you=%d\r\n",result);
		Ov7725_vsync = 0;			
	}
}

void jiance(void)
{
	printf("jiance\r\n");
  jiance1();
	if(zhangai_flag==0) jiance0();
   else               jiance2();	

}

void ceshi(void)
{
	while(1)
	{
		TIM3_Mode_Config(100);
			delay_ms(500);
		TIM3_Mode_Config(200);
			delay_ms(500);
		TIM3_Mode_Config(300);
			delay_ms(500);
		TIM3_Mode_Config(400);
			delay_ms(500);
		TIM3_Mode_Config(500);
			delay_ms(500);
		TIM3_Mode_Config(600);
			delay_ms(500);
		TIM3_Mode_Config(500);
			delay_ms(500);
		TIM3_Mode_Config(400);
			delay_ms(500);
		TIM3_Mode_Config(300);
			delay_ms(500);
		TIM3_Mode_Config(200);
			delay_ms(500);
	}		
}



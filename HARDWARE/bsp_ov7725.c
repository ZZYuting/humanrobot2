#include "bsp_ov7725.h"
#include "bsp_sccb.h"
#include "bsp_ili9341_lcd.h"

typedef struct Reg
{
	uint8_t Address; //寄存器地址
	uint8_t Value;   //寄存器值
}Reg_Info;

/* 寄存器参数配置 */
Reg_Info Sensor_Config[] =
{
	{CLKRC,     0x00}, /*时钟配置clock config*/
	{COM7,      0x46}, /*QVGA RGB565 */
    {HSTART,    0x3f},
	{HSIZE,     0x50},
	{VSTRT,     0x03},
	{VSIZE,     0x78},
	{HREF,      0x00},
	{HOutSize,  0x50},
	{VOutSize,  0x78},
	{EXHCH,     0x00},
	/*DSP控制 DSP control*/
	{TGT_B,     0x7f},
	{FixGain,   0x09},
	{AWB_Ctrl0, 0xe0},
	{DSP_Ctrl1, 0xff},
	{DSP_Ctrl2, 0x20},
	{DSP_Ctrl3,	0x00},
	{DSP_Ctrl4, 0x00},
	/*AGC AEC AWB*/
	{COM8,		0xf0},
	{COM4,	    0x81}, /*锁相环设计配置Pll AEC CONFIG*/
	{COM6,		0xc5},
	{COM9,		0x21},
	{BDBase,	0xFF},
	{BDMStep,	0x01},
	{AEW,		0x34},
	{AEB,		0x3c},
	{VPT,		0xa1},
	{EXHCL,		0x00},
	{AWBCtrl3,  0xaa},
	{COM8,		0xff},
	{AWBCtrl1,  0x5d},

	{EDGE1,		0x0a},
	{DNSOff,	0x01},
	{EDGE2,		0x01},
	{EDGE3,		0x01},

	{MTX1,		0x5f},
	{MTX2,		0x53},
	{MTX3,		0x11},
	{MTX4,		0x1a},
	{MTX5,		0x3d},
	{MTX6,		0x5a},
	{MTX_Ctrl,  0x1e},

	{BRIGHT,	0x00},
	{CNST,		0x25},
	{USAT,		0x65},
	{VSAT,		0x65},
	{UVADJ0,	0x81},
	{SDE,		0x06},	
    /*伽马配置GAMMA config*/
	{GAM1,		  0x0c},
	{GAM2,		  0x16},
	{GAM3,		  0x2a},
	{GAM4,		  0x4e},
	{GAM5,		  0x61},
	{GAM6,		  0x6f},
	{GAM7,		  0x7b},
	{GAM8,		  0x86},
	{GAM9,		  0x8e},
	{GAM10,		  0x97},
	{GAM11,		  0xa4},
	{GAM12,		  0xaf},
	{GAM13,		  0xc5},
	{GAM14,		  0xd7},
	{GAM15,		  0xe8},
	{SLOP,		  0x20},

	{HUECOS,	  0x80},
	{HUESIN,	  0x80},
	{DSPAuto,	  0xff},
	{DM_LNL,	  0x00},
	{BDBase,	  0x99},
	{BDMStep,	  0x03},
	{LC_RADI,	  0x00},
	{LC_COEF,	  0x13},
	{LC_XC,		  0x08},
	{LC_COEFB,    0x14},
	{LC_COEFR,    0x17},
	{LC_CTR,	  0x05},
	
	{COM3,		  0xd0},/*水平镜像Horizontal mirror image*/
	/*夜间自动帧速率控制模式night mode auto frame rate control*/
	{COM5,		  0xf5},	 /*在夜视环境下，自动降低帧率，保证低照度画面质量*/
	//{COM5,		0x31},	/*夜视环境帧率不变*/
};

u8 OV7725_REG_NUM = sizeof(Sensor_Config)/sizeof(Sensor_Config[0]);	//结构体数组成员数目

uint8_t Ov7725_vsync = 0;//帧同步信号标志，在中断函数和main函数里面使用

/* 函数名：FIFO_GPIO_Config
 * 描述  ：FIFO GPIO配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无 */
static void FIFO_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | 
	                          RCC_APB2Periph_GPIOB | 
	                          RCC_APB2Periph_GPIOC | 
	                          RCC_APB2Periph_GPIOD , ENABLE);
	
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		/* 1W LED 灯控制 */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		//GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_8);	
		/*PD3(FIFO_WEN--FIFO写使能)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOD, &GPIO_InitStructure);	
		/*PB5(FIFO_WRST--FIFO写复位)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		/*PA2(FIFO_RRST--FIFO读复位) PA3(FIFO_OE--FIFO输出使能)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
		/*PC5(FIFO_RCLK-FIFO读时钟)*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*PB8-PB15(FIFO_DATA--FIFO输出数据)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    FIFO_CS_L();	  					/*拉低使FIFO输出使能*/
    FIFO_WE_H();   						/*拉高使FIFO写允许*/
}

void Ov7725_GPIO_Config(void)
{
	SCCB_GPIO_Config();
	FIFO_GPIO_Config();
}

/* 函数名：VSYNC_GPIO_Configuration
 * 描述  ：OV7725 GPIO配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无 */
static void VSYNC_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  /*PA0---VSYNC*/
	
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* 函数名：VSYNC_NVIC_Configuration
 * 描述  ：VSYNC中断配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无*/
static void VSYNC_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* 函数名：VSYNC_EXTI_Configuration
 * 描述  ：OV7725 VSYNC中断管脚配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无*/
/*               ___                            ___
 * VSYNC:     __|   |__________________________|   |__     
 */
static void VSYNC_EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ; /*上升沿触发*/
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_GenerateSWInterrupt(EXTI_Line0);	/*中断挂到 EXTI_Line0  线*/
}

/************************************************
 * 函数名：VSYNC_Init
 * 描述  ：OV7725 VSYNC中断相关配置
 * 输入  ：无
 * 输出  ：无
 * 注意  ：无
 ************************************************/
void VSYNC_Init(void)
{
    VSYNC_GPIO_Configuration();
    VSYNC_EXTI_Configuration();
    VSYNC_NVIC_Configuration();
}

/* 函数名：Sensor_Init
 * 描述  ：Sensor初始化
 * 输入  ：无
 * 输出  ：返回1成功，返回0失败
 * 注意  ：无*/
ErrorStatus Ov7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;	
	
	//DEBUG("ov7725 Register Config Start......");
	
	if( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*复位sensor */
	{
		//DEBUG("sccb write data error");		
		return ERROR ;
	}	

	if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* 读取sensor ID号*/
	{
		//DEBUG("read id faild");		
		return ERROR;
	}
	//DEBUG("Sensor ID is 0x%x", Sensor_IDCode);	
	
	if(Sensor_IDCode == OV7725_ID)
	{
		for( i = 0 ; i < OV7725_REG_NUM ; i++ )
		{
			if( 0 == SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value) )
			{                
				//DEBUG("write reg faild", Sensor_Config[i].Address);
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	//DEBUG("ov7725 Register Config Success");
	
	return SUCCESS;
}
//长：320  高：240
//void ImagDisp(void)
//{
//	uint16_t i, j;
//	uint16_t Camera_Data;
//	for(i = 0; i < 240; i++)
//	{
//		for(j = 0; j < 320; j++)
//		{
//			READ_FIFO_PIXEL(Camera_Data);		// 从FIFO读出一个rgb565像素到Camera_Data变量
//			LCD_WR_Data(Camera_Data);
//		}
//	}
//}

void sort(int * arr,int length)//???? 
{
	char i,j;
	char tempIndex;
	int temp;
	
	for(i=0;i<length;i++)
	{
		tempIndex=i;
		
		for(j=i+1;j<length;j++)
		{
			if(arr[j]<arr[tempIndex])
			{
				tempIndex=j;
			}
		}
		
		temp = arr[i];
		arr[i]=arr[tempIndex];
		arr[tempIndex]=temp;
	}

}

int getAverage(int a ,int b, int c) 
{
	int max,min,medum;
	
	int arr[3];
	
	arr[0]=a;
	arr[1]=b;
	arr[2]=c;

	sort(arr,3);
	
	max		=arr[2];
	min		=arr[0];
	medum	=arr[1];
		

	if(max-medum<20&& medum-min<20)
	{
		return (max+medum+min)/3;
	}
	
	if(max-medum<20)
	{
		return (max+medum)/2; 
	}
	
	
	if(medum-min<20)
	{
		return (medum+min)/2;
	}
	
	return 0;	

}
int dealArr2(int * arr)
{
	
	int part1[7]={0,0,0,0,0,0,0};
	char part1Length =0;
	int part2[7]={0,0,0,0,0,0,0} ;
	char part2Length =0;
	char i=1;
	int result =0;
	
	for(i=0;i<6;i++)
	{
		 if(arr[i]==0)
		 {
				continue;
		 }
		 
		part1Length++;
		part1[i]=arr[i];

		
		if(arr[i+1]-arr[i]>10)
		{
			i++;
			break;
		}
		
		
	}
	
	for(i;i<6;i++)
	{

		if(arr[i]==0)
		{
		 	continue;
		}

		
		if(arr[i+1]-arr[i]>8)//??????? 
		{
			continue;	
		}		


		part2[part2Length]=arr[i];
		part2Length++;
	}
	
	
	printf("\r\n");


	if(part1Length>part2Length)
	{
		
		for(i=0;i<part1Length;i++)
		{
			result+=part1[i];
		}

		result/=part1Length;
	
	}
	else
	{
			for(i=0;i<part2Length;i++)
			{
				result+=part2[i];
			}

			result/=part2Length;
	}
	
	
	return result;
	
	
}
	
int dealArr1(int * arr)
{
	
	int part1[6]={0,0,0,0,0,0};
	char part1Length =0;
	int part2[6]={0,0,0,0,0,0} ;
	char part2Length =0;
	char i=1;
	int result =0;
	
	for(i=0;i<5;i++)
	{	 
		part1Length++;
		part1[i]=arr[i];

		
		if(arr[i+1]-arr[i]>10)
		{
			i++;
			break;
		}
		
	}
	
	for(i;i<5;i++)
	
	{
		if(arr[i+1]-arr[i]>10)
		{
			continue;	
		}		
		part2[part2Length]=arr[i];
		part2Length++;
	}
	

	if(part1Length>part2Length)
	{
		
		for(i=0;i<part1Length;i++)
		{
			result+=part1[i];
		}

		result/=part1Length;
	
	}
	else
	{
			for(i=0;i<part2Length;i++)
			{
				result+=part2[i];
			}

			result/=part2Length;
	}
	
	

	return result;
}
 

char biaozhun(void)
{
	int slope =0;//??	    
	int i=0,j=0;
	int a=0,b=0,c=0;
	unsigned short int Camera_Data,B,G,R,flageColor;
	char blackPeixs=0;
	char scanfControler= 0;//????   
	char lineIndex=1;//???????? 
	char blackLinesEachLine = 0;//?????????? 
	char jIndex =0; 
	
	int mapGetCenterJ[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};//???????? 
	int jtemp1=0;
	int jtemp2=0;
	 
//	printf("\r\n");

	for(i=0;i<240;i++)
	{
	
		if(i==48*lineIndex)//?? ???? 
		{
			scanfControler=1;
		} 
		
		if(i==48*lineIndex+1)//????????????? ?:?????????? 
		{
			
			lineIndex++;
			scanfControler =0;
			blackLinesEachLine = 0;
			blackPeixs=0;
		} 
		
			for(j=0;j<320;j++)
			{
				 
				READ_FIFO_PIXEL(Camera_Data);
				
				B=Camera_Data & 0x001f;
				G=(Camera_Data>>5)&0x003f;
				R=(Camera_Data>>11)&0x001f;
			
				if(B >= 10 || G >= 20|| R >= 10)//????? 
				{
					flageColor=0xffff;			
						if(scanfControler)
						{					
							if(blackPeixs>8&&blackPeixs<30)
							{
							 	jtemp2=j;
								mapGetCenterJ[lineIndex-1][blackLinesEachLine]=(jtemp1+jtemp2)/2;
								blackLinesEachLine++;
							}
								
							blackPeixs=0;	
						}
							
				}
				else//????? 
				{
					flageColor =0x0000;
					
					if(scanfControler)
					{
						if(blackPeixs==0)//??????? 
						{
							jtemp1 = j; 
						}
						
						blackPeixs++;//???????
						flageColor =0xff00;	
						if(blackPeixs>6&&blackPeixs<30)
						{
						 	flageColor =0x00ff;
						}
					}
					 
				}
					//Camera_Data
					//flageColor
					LCD_WR_Data(flageColor);
			}
	}
	
	
	a = mapGetCenterJ[1][0]-mapGetCenterJ[0][0];
	b = mapGetCenterJ[2][0]-mapGetCenterJ[1][0];
	c = mapGetCenterJ[3][0]-mapGetCenterJ[2][0];
	
	slope=getAverage(a,b,c);
	
	
	
	if(slope>15&&slope<=80)//??? 
	{
		return 2;
	}
	
	if(slope>6&&slope<=15)//??? 
	{
		return 1;
	}
	
	if(-10<slope&&slope<=6)//?? 
	{
		return 3;
	}
	
	if(slope>-15&&slope<=-10)//??? 
	{
		return 3;
	}
	
	if(slope>-30&&slope<=-15)//??? 
	{
		return 3;
	}
	
	return 3;
}
	 
	 
char getdistance(void)
{
	int i,j;
	
	unsigned short int Camera_Data,B,G,R,flageColor;	
	
	int j1temps[7]={0,0,0,0,0,0,0};//???????????j??? 
	int j2temps[7]={0,0,0,0,0,0,0};//???????j???
	
	char blackPeixs[7]={0,0,0,0,0,0,0};//???????
	int blackCenter[7]={0,0,0,0,0,0,0};//?????????????? 
	
	char flageIndex[7]={1,1,1,1,1,1,1};//??????????????,
	
	char scanfControl =0; //???? 
	char lineIndex =0;//??????? 
	char usefulLineCount=0; 
	int result = 0;
	
	 
	for(i=0;i<240;i++)
	{
			
			
			for(j=0;j<320;j++)
			{
				
				
				if( j%40==0 && j!=0 && j!=320)//?j? 40 80 120 160 200 240 280  ??? 
				
				{
					scanfControl=1; 
					lineIndex =j/40-1;
				}
				
				else
				
				{
					scanfControl=0;
				} 
				
				READ_FIFO_PIXEL(Camera_Data);
				
				B=Camera_Data & 0x001f;
				G=(Camera_Data>>5)&0x003f;
				R=(Camera_Data>>11)&0x001f;
				
				
				
				
				if(B >= 10|| G >= 23|| R >= 10)//????? 
				{
											
					flageColor =0xffff;
					
					if(scanfControl)
					{
						if( flageIndex[lineIndex] && blackPeixs[lineIndex]>7 && blackPeixs[lineIndex]<30)//??????  
						{
							j2temps[lineIndex] =i;
							flageIndex[lineIndex]=0;
						}
					
					}
					
				}
				else//????? 
				{					
					flageColor =0x0000; 
					
					if(scanfControl)
					{
						
						flageColor = 0xff00;//??? 
						
						if(blackPeixs[lineIndex]==0)//?????????? 
						{
							 j1temps[lineIndex]=i;
						} 
						
						blackPeixs[lineIndex]++;//???? 
						
					}

					if(i==239 && flageIndex[lineIndex] && blackPeixs[lineIndex]>10 && blackPeixs[lineIndex]<30 && j1temps[lineIndex]>210)
					{
					
						j2temps[lineIndex]=239;
						flageIndex[lineIndex]=0;
					}
				
				}
					 //Camera_Data
					 //flageColor
					LCD_WR_Data(flageColor);
			}
	}
	
	for(i=0;i<7;i++)
	{
		if(flageIndex[i] && j1temps[i]>200)
		{
			j2temps[i]=240;
			flageIndex[i]=0;
		} 
		
	}

	
	
	for(i=0;i<7;i++)
	{
	
		blackCenter[i] =(j1temps[i]+j2temps[i])/2;
		
		
		
		if(blackCenter[i])
		{
			usefulLineCount ++;
		}
		
	}
	
	
//	printf("\r\n");
	
	if(usefulLineCount<=5) 
	{
		return 240;
	}
	
	sort(j1temps,7);
	
	

	result =240-dealArr2(j1temps);
	
	
	
	
	return result;
	
}


char ready_to(void)
{
	int i,j;
	unsigned short int Camera_Data,B,G,R,flageColor;	
	int j1temps[7]={0,0,0,0,0,0,0};//???????????j??? 
	int j2temps[7]={0,0,0,0,0,0,0};//???????j???
	int slopes[6]={0,0,0,0,0,0};//????,?:blackCenter[i+1]- blackCenter[i]
	char blackPeixs[7]={0,0,0,0,0,0,0};//???????
	int blackCenter[7]={0,0,0,0,0,0,0};//?????????????? 
	char flageIndex[7]={1,1,1,1,1,1,1};//??????????????,

	char scanfControl =0; //???? 
	char lineIndex =0;//??????? 
	int result = 0;

	for(i=0;i<240;i++)
	{
			for(j=0;j<320;j++)
			{
				
				if( j%40==0 && j!=0 && j!=320)//?j? 40 80 120 160 200 240 280  ??? 
				
				{
					scanfControl=1; 
					lineIndex =j/40-1;
				}
				else
				{
					scanfControl=0;
				} 
				
				READ_FIFO_PIXEL(Camera_Data);
				
				B=Camera_Data & 0x001f;
				G=(Camera_Data>>5)&0x003f;
				R=(Camera_Data>>11)&0x001f;

				if(B >= 10|| G >= 23|| R >= 10)//????? 
				{
										
					flageColor =0xffff;
					
					if(scanfControl)
					{
						if( flageIndex[lineIndex] && blackPeixs[lineIndex]>7 && blackPeixs[lineIndex]<30)//??????  
						{
							j2temps[lineIndex] =i;
							flageIndex[lineIndex]=0;
						}
						
					}
				
				}
				else//????? 
				{					
					flageColor =0x0000;//??	 
					
					if(scanfControl)
					{
						
						flageColor = 0xff00;//??? 
						
						if(blackPeixs[lineIndex]==0)//?????????? 
						{
							 j1temps[lineIndex]=i;
						} 
						
						blackPeixs[lineIndex]++;//???? 
						
						if(i==239 && flageIndex[lineIndex] && blackPeixs[lineIndex]>10 && blackPeixs[lineIndex]<30)//??????????????? 
						{
							j2temps[lineIndex]=239;
							flageIndex[lineIndex]=0;
						}
					}
				
				}
					LCD_WR_Data(Camera_Data);
			}
	}
	for(i=0;i<7;i++)
	{
		if(flageIndex[i] && j1temps[lineIndex]>210)
		{
			j2temps[i]=240;
		} 
		
	}

	
	
	for(i=0;i<7;i++)
	{
	
		blackCenter[i] =(j1temps[i]+j2temps[i])/2;
		
	}


	for(i=0;i<6;i++)
	{
		slopes[i]=j1temps[i+1]-j1temps[i];
		
	}
	
	sort(slopes,6);
	
	
	result = dealArr1(slopes);
	
	printf("\r\n根据障碍调整自己的位置：斜率结果=%d\r\n",result);
	
	
	if(result>=6) //????
	{
	//	printf("4,右");
		return 3; //right
	}
	
	if(result<-1) //????
	{
	//	printf("1,左");
		return 1;  //left
	
	}
	
	return 3;	  // zhixing
	
}

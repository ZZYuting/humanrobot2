
#include "led.h"
#include "stm32f10x.h"
#include"stdio.h"

void SetJointAngle_R(float angle)
{
  angle=(u16)(5.56*angle+249);  //参数可变
  TIM_SetCompare2(TIM3,angle);  //这里改变占空比，这里写的值是TIM_Pulse

}

void SetJointAngle_L(float angle)
{
  angle=(u16)(5.56*angle+249);  //参数可变
  TIM_SetCompare1(TIM3,angle);  //这里改变占空比，这里写的值是TIM_Pulse

}

void hand_move1(void)
{
	SetJointAngle_R(85);
	SetJointAngle_L(95);
}
void hand_move2(void)
{					   
	SetJointAngle_R(95);
	SetJointAngle_L(85);
}
void PWM_OUTPUT(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;		      //TIM3 CH1 A6 CH2 A7 																					   //	  CH2 A7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									      
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									 
  GPIO_Init(GPIOA, &GPIO_InitStructure);											   

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;		          // TIM3   CH3 B0 CH4 B1																					   //	  CH2 A7
  GPIO_Init(GPIOB, &GPIO_InitStructure);											   

  TIM_TimeBaseStructure.TIM_Period = 10000-1;											   
  TIM_TimeBaseStructure.TIM_Prescaler = 72*2-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_Cmd(TIM3, ENABLE);


}
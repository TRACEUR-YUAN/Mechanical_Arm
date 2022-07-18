#include "steeringengine10.h"

void SteeringEngine10_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteeringEngine10_GPIO_CLK_Cmd(SteeringEngine10_GPIO_CLK, ENABLE);
	
	GPIO_PinAFConfig(SteeringEngine10_GPIO, SteeringEngine10_GPIOSource, SteeringEngine10_GPIO_AF);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = SteeringEngine10_GPIO_Pin;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(SteeringEngine10_GPIO, &GPIO_InitStructure);	
}

void SteeringEngine10_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	SteeringEngine10_TIM_CLK_Cmd(SteeringEngine10_TIM_CLK, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 200;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8399;
	
	TIM_TimeBaseInit(SteeringEngine10_TIM, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
//		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	TIM_OC1Init(SteeringEngine10_TIM, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(SteeringEngine10_TIM, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(SteeringEngine10_TIM, ENABLE);
	
	TIM_Cmd(SteeringEngine10_TIM, ENABLE);	
	
	TIM_CtrlPWMOutputs(SteeringEngine10_TIM, ENABLE);
}

void SteeringEngine10_Initialization(void)
{
	SteeringEngine10_GPIO_Init();
	SteeringEngine10_TIM_Init();
}

void SteeringEngine10_SetAngle(uint16_t angle)
{
	TIM_SetCompare1(SteeringEngine10_TIM, (int)((float)angle / 90 * 10 + 15));
}

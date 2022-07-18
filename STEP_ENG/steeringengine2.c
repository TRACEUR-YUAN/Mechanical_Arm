#include "steeringengine2.h"

void SteeringEngine2_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteeringEngine2_GPIO_CLK_Cmd(SteeringEngine2_GPIO_CLK, ENABLE);
	
	GPIO_PinAFConfig(SteeringEngine2_GPIO, SteeringEngine2_GPIOSource, SteeringEngine2_GPIO_AF);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = SteeringEngine2_GPIO_Pin;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(SteeringEngine2_GPIO, &GPIO_InitStructure);	
}

void SteeringEngine2_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	SteeringEngine2_TIM_CLK_Cmd(SteeringEngine2_TIM_CLK, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 200;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 16799;
	
	TIM_TimeBaseInit(SteeringEngine2_TIM, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 15;
	
	TIM_OC1Init(SteeringEngine2_TIM, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(SteeringEngine2_TIM, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(SteeringEngine2_TIM, ENABLE);
	
	TIM_Cmd(SteeringEngine2_TIM, ENABLE);	
	
	TIM_CtrlPWMOutputs(SteeringEngine2_TIM, ENABLE);
}

void SteeringEngine2_Initialization(void)
{
	SteeringEngine2_GPIO_Init();
	SteeringEngine2_TIM_Init();
}

void SteeringEngine2_SetAngle(uint16_t angle)
{
	TIM_SetCompare1(SteeringEngine2_TIM, (int)((float)angle / 90 * 10 + 15));
}

#include "steeringengine3.h"

void SteeringEngine3_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteeringEngine3_GPIO_CLK_Cmd(SteeringEngine3_GPIO_CLK, ENABLE);
	
	GPIO_PinAFConfig(SteeringEngine3_GPIO, SteeringEngine3_GPIOSource , SteeringEngine3_GPIO_AF);
	GPIO_PinAFConfig(SteeringEngine3_GPIO, GPIO_PinSource3 , SteeringEngine3_GPIO_AF);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = SteeringEngine3_GPIO_Pin | GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(SteeringEngine3_GPIO, &GPIO_InitStructure);	
}

void SteeringEngine3_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	SteeringEngine3_TIM_CLK_Cmd(SteeringEngine3_TIM_CLK, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 200;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 16799;
	
	TIM_TimeBaseInit(SteeringEngine3_TIM, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 15;	
	TIM_OC1Init(SteeringEngine3_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SteeringEngine3_TIM, TIM_OCPreload_Enable);
	TIM_OC2Init(SteeringEngine3_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SteeringEngine3_TIM, TIM_OCPreload_Enable);
	

	
	TIM_ARRPreloadConfig(SteeringEngine3_TIM, ENABLE);
	
	TIM_Cmd(SteeringEngine3_TIM, ENABLE);	
	
	TIM_CtrlPWMOutputs(SteeringEngine3_TIM, ENABLE);
}

void SteeringEngine3_Initialization(void)
{
	SteeringEngine3_GPIO_Init();
	SteeringEngine3_TIM_Init();
}

void SteeringEngine3_SetAngle(uint16_t angle)
{
	TIM_SetCompare1(SteeringEngine3_TIM, (int)((float)angle / 90 * 10 + 15));
}

void SteeringEngine4_SetAngle(uint16_t angle)
{
	TIM_SetCompare2(SteeringEngine3_TIM, (int)((float)angle / 90 * 10 + 15));
}

#ifndef __STEERINGENGINE2_H
#define __STEERINGENGINE2_H

#include "stm32f4xx.h"

#define SteeringEngine2_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteeringEngine2_GPIO_CLK    RCC_AHB1Periph_GPIOB
#define SteeringEngine2_GPIO      	GPIOB
#define SteeringEngine2_GPIO_Pin  	GPIO_Pin_8
#define SteeringEngine2_GPIOSource 	GPIO_PinSource8
#define SteeringEngine2_GPIO_AF 			GPIO_AF_TIM10

#define SteeringEngine2_TIM_CLK_Cmd RCC_APB2PeriphClockCmd
#define SteeringEngine2_TIM_CLK 		RCC_APB2Periph_TIM10
#define SteeringEngine2_TIM 				TIM10

void SteeringEngine2_GPIO_Init(void);

void SteeringEngine2_TIM_Init(void);

void SteeringEngine2_Initialization(void);

void SteeringEngine2_SetAngle(uint16_t angle);

#endif


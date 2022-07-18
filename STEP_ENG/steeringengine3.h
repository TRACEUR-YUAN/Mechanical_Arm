#ifndef __STEERINGENGINE3_H
#define __STEERINGENGINE3_H

#include "stm32f4xx.h"

#define SteeringEngine3_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteeringEngine3_GPIO_CLK    RCC_AHB1Periph_GPIOA
#define SteeringEngine3_GPIO      	GPIOA
#define SteeringEngine3_GPIO_Pin  	GPIO_Pin_2
#define SteeringEngine3_GPIOSource 	GPIO_PinSource2
#define SteeringEngine3_GPIO_AF 			GPIO_AF_TIM9

#define SteeringEngine3_TIM_CLK_Cmd RCC_APB2PeriphClockCmd
#define SteeringEngine3_TIM_CLK 		RCC_APB2Periph_TIM9
#define SteeringEngine3_TIM 				TIM9

void SteeringEngine3_GPIO_Init(void);

void SteeringEngine3_TIM_Init(void);

void SteeringEngine3_Initialization(void);

void SteeringEngine3_SetAngle(uint16_t angle);

void SteeringEngine4_SetAngle(uint16_t angle);

#endif


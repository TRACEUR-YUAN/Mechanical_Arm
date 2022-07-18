#ifndef __STEERINGENGINE10_H
#define __STEERINGENGINE10_H

#include "stm32f4xx.h"
//#include "systick.h"

#define SteeringEngine10_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteeringEngine10_GPIO_CLK    RCC_AHB1Periph_GPIOF
#define SteeringEngine10_GPIO      	GPIOF
#define SteeringEngine10_GPIO_Pin  	GPIO_Pin_9
#define SteeringEngine10_GPIOSource 	GPIO_PinSource9
#define SteeringEngine10_GPIO_AF 			GPIO_AF_TIM14

#define SteeringEngine10_TIM_CLK_Cmd RCC_APB1PeriphClockCmd
#define SteeringEngine10_TIM_CLK 		RCC_APB1Periph_TIM14
#define SteeringEngine10_TIM 				TIM14

void SteeringEngine10_GPIO_Init(void);

void SteeringEngine10_TIM_Init(void);

void SteeringEngine10_Initialization(void);

void SteeringEngine10_SetAngle(uint16_t angle);

#endif


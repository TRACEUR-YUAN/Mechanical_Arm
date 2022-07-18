#ifndef __STEERINGENGINE1_H
#define __STEERINGENGINE1_H

#include "stm32f4xx.h"
//#include "systick.h"

#define SteeringEngine1_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteeringEngine1_GPIO_CLK    RCC_AHB1Periph_GPIOB
#define SteeringEngine1_GPIO      	GPIOB
#define SteeringEngine1_GPIO_Pin  	GPIO_Pin_9
#define SteeringEngine1_GPIOSource 	GPIO_PinSource9
#define SteeringEngine1_GPIO_AF 			GPIO_AF_TIM11

#define SteeringEngine1_TIM_CLK_Cmd RCC_APB2PeriphClockCmd
#define SteeringEngine1_TIM_CLK 		RCC_APB2Periph_TIM11
#define SteeringEngine1_TIM 				TIM11

void SteeringEngine1_GPIO_Init(void);

void SteeringEngine1_TIM_Init(void);

void SteeringEngine1_Initialization(void);

void SteeringEngine1_SetAngle(uint16_t angle);

#endif


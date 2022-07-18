#ifndef __STEPPINGMOTOR3_H
#define __STEPPINGMOTOR3_H

#include "stm32f4xx.h"
#include "includes.h"


#define SteppingMotor3_PUL_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor3_PUL_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor3_PUL_GPIO GPIOD
#define SteppingMotor3_PUL_GPIO_Pin GPIO_Pin_6

#define SteppingMotor3_DIR_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor3_DIR_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor3_DIR_GPIO GPIOD
#define SteppingMotor3_DIR_GPIO_Pin GPIO_Pin_7

#define SteppingMotor3_ENA_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor3_ENA_GPIO_CLK RCC_AHB1Periph_GPIOG
#define SteppingMotor3_ENA_GPIO GPIOG
#define SteppingMotor3_ENA_GPIO_Pin GPIO_Pin_9

void SteppingMotor3_PUL_GPIO_Init(void);

void SteppingMotor3_DIR_GPIO_Init(void);

void SteppingMotor3_ENA_GPIO_Init(void);

void SteppingMotor3_Initialization(void);

void SteppingMotor3_Enable(void);

void SteppingMotor3_Disable(void);

void SteppingMotor3_Turn(int pulse);

#endif


#ifndef __STEPPINGMOTOR1_H
#define __STEPPINGMOTOR1_H

#include "stm32f4xx.h"
#include "includes.h"

#define SteppingMotor1_PUL_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor1_PUL_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor1_PUL_GPIO GPIOD
#define SteppingMotor1_PUL_GPIO_Pin GPIO_Pin_0

#define SteppingMotor1_DIR_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor1_DIR_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor1_DIR_GPIO GPIOD
#define SteppingMotor1_DIR_GPIO_Pin GPIO_Pin_1

#define SteppingMotor1_ENA_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor1_ENA_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor1_ENA_GPIO GPIOD
#define SteppingMotor1_ENA_GPIO_Pin GPIO_Pin_2

void SteppingMotor1_PUL_GPIO_Init(void);

void SteppingMotor1_DIR_GPIO_Init(void);

void SteppingMotor1_ENA_GPIO_Init(void);

void SteppingMotor1_Initialization(void);

void SteppingMotor1_Enable(void);

void SteppingMotor1_Disable(void);

void SteppingMotor1_Turn(int pulse);

#endif


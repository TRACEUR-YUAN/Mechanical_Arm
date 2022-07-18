#ifndef __STEPPINGMOTOR2_H
#define __STEPPINGMOTOR2_H

#include "stm32f4xx.h"
#include "includes.h"

#define SteppingMotor2_PUL_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor2_PUL_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor2_PUL_GPIO GPIOD
#define SteppingMotor2_PUL_GPIO_Pin GPIO_Pin_3

#define SteppingMotor2_DIR_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor2_DIR_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor2_DIR_GPIO GPIOD
#define SteppingMotor2_DIR_GPIO_Pin GPIO_Pin_4

#define SteppingMotor2_ENA_GPIO_CLK_Cmd RCC_AHB1PeriphClockCmd
#define SteppingMotor2_ENA_GPIO_CLK RCC_AHB1Periph_GPIOD
#define SteppingMotor2_ENA_GPIO GPIOD
#define SteppingMotor2_ENA_GPIO_Pin GPIO_Pin_5

void SteppingMotor2_PUL_GPIO_Init(void);

void SteppingMotor2_DIR_GPIO_Init(void);

void SteppingMotor2_ENA_GPIO_Init(void);

void SteppingMotor2_Initialization(void);

void SteppingMotor2_Enable(void);

void SteppingMotor2_Disable(void);

void SteppingMotor2_Turn(int pulse);

#endif


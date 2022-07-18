#include "steppingmotor1.h"


void SteppingMotor1_PUL_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor1_PUL_GPIO_CLK_Cmd(SteppingMotor1_PUL_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor1_PUL_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor1_PUL_GPIO, &GPIO_InitStructure);
}

void SteppingMotor1_DIR_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor1_DIR_GPIO_CLK_Cmd(SteppingMotor1_DIR_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor1_DIR_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor1_DIR_GPIO, &GPIO_InitStructure);
}

void SteppingMotor1_ENA_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor1_ENA_GPIO_CLK_Cmd(SteppingMotor1_ENA_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor1_ENA_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor1_ENA_GPIO, &GPIO_InitStructure);
}

void SteppingMotor1_Initialization(void)
{
	SteppingMotor1_PUL_GPIO_Init();
	
	SteppingMotor1_DIR_GPIO_Init();
	
	SteppingMotor1_ENA_GPIO_Init();
}

void SteppingMotor1_Enable(void)
{
	GPIO_SetBits(SteppingMotor1_ENA_GPIO, SteppingMotor1_ENA_GPIO_Pin);
}

void SteppingMotor1_Disable(void)
{
	GPIO_ResetBits(SteppingMotor1_ENA_GPIO, SteppingMotor1_ENA_GPIO_Pin);
}

void SteppingMotor1_Turn(int pulse)
{
	OS_ERR err;
	uint16_t i = 0;
	if (pulse > 0)
	{
		GPIO_SetBits(SteppingMotor1_DIR_GPIO, SteppingMotor1_DIR_GPIO_Pin);
	}
	else
	{
		GPIO_ResetBits(SteppingMotor1_DIR_GPIO, SteppingMotor1_DIR_GPIO_Pin);
		pulse = -pulse;
	}
	for (i = 0; i < pulse; i++)
	{
			GPIO_SetBits(SteppingMotor1_PUL_GPIO, SteppingMotor1_PUL_GPIO_Pin);
			OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_NON_STRICT,&err);
			GPIO_ResetBits(SteppingMotor1_PUL_GPIO, SteppingMotor1_PUL_GPIO_Pin);
			OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_NON_STRICT,&err);
	}
}

#include "steppingmotor3.h"
#include "os.h"

void SteppingMotor3_PUL_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor3_PUL_GPIO_CLK_Cmd(SteppingMotor3_PUL_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor3_PUL_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor3_PUL_GPIO, &GPIO_InitStructure);
}

void SteppingMotor3_DIR_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor3_DIR_GPIO_CLK_Cmd(SteppingMotor3_DIR_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor3_DIR_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor3_DIR_GPIO, &GPIO_InitStructure);
}

void SteppingMotor3_ENA_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SteppingMotor3_ENA_GPIO_CLK_Cmd(SteppingMotor3_ENA_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = SteppingMotor3_ENA_GPIO_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(SteppingMotor3_ENA_GPIO, &GPIO_InitStructure);
}

void SteppingMotor3_Initialization(void)
{
	SteppingMotor3_PUL_GPIO_Init();
	
	SteppingMotor3_DIR_GPIO_Init();
	
	SteppingMotor3_ENA_GPIO_Init();
}

void SteppingMotor3_Enable(void)
{
	GPIO_ResetBits(SteppingMotor3_ENA_GPIO, SteppingMotor3_ENA_GPIO_Pin);
}

void SteppingMotor3_Disable(void)
{
	GPIO_SetBits(SteppingMotor3_ENA_GPIO, SteppingMotor3_ENA_GPIO_Pin);
}

void SteppingMotor3_Turn(int pulse)
{
	OS_ERR err;
	uint16_t i = 0;
	if (pulse > 0)
	{
		GPIO_SetBits(SteppingMotor3_DIR_GPIO, SteppingMotor3_DIR_GPIO_Pin);
	}
	else
	{
		GPIO_ResetBits(SteppingMotor3_DIR_GPIO, SteppingMotor3_DIR_GPIO_Pin);
		pulse = -pulse;
	}
	for (i = 0; i < pulse; i++)
	{
			GPIO_SetBits(SteppingMotor3_PUL_GPIO, SteppingMotor3_PUL_GPIO_Pin);
			OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_NON_STRICT,&err); 
			GPIO_ResetBits(SteppingMotor3_PUL_GPIO, SteppingMotor3_PUL_GPIO_Pin);
			OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_NON_STRICT,&err); 
	}
}

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"
#include "ps2.h"
#include "pwm.h"
#include "steppingmotor1.h"
#include "steppingmotor2.h"
#include "steppingmotor3.h"
#include "steeringengine1.h"
#include "steeringengine2.h"
#include "steeringengine3.h"
#include "steeringengine10.h"

uint8_t PS2_Flag = 0;

//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//������������ȼ����������֣���ջ��TCB����������
#define START_TASK_PRIO 3
#define START_STK_SIZE 512
OS_TCB StartTaskTCB;
CPU_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);

#define LED0_TASK_PRIO 4
#define LED0_STK_SIZE 128
OS_TCB LED0TaskTCB;
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);

#define LED1_TASK_PRIO 5
#define LED1_STK_SIZE 128
OS_TCB LED1TaskTCB;
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
void led1_task(void *p_arg);

#define PS2_TASK_PRIO 6
#define PS2_STK_SIZE 128
OS_TCB PS2TaskTCB;
CPU_STK PS2_TASK_STK[PS2_STK_SIZE];
void ps2_task(void *p_arg);

#define STEERINGUP_TASK_PRIO 7
#define STEERINGUP_STK_SIZE 128
OS_TCB SteeringupTaskTCB;
CPU_STK STEERINGUP_TASK_STK[STEERINGUP_STK_SIZE];
void steeringup_task(void *p_arg);

#define STEERINGDOWN_TASK_PRIO 14
#define STEERINGDOWN_STK_SIZE 128
OS_TCB SteeringdownTaskTCB;
CPU_STK STEERINGDOWN_TASK_STK[STEERINGDOWN_STK_SIZE];
void steeringdown_task(void *p_arg);

#define STEERINGSMALL_TASK_PRIO 14
#define STEERINGSMALL_STK_SIZE 128
OS_TCB SteeringsmallTaskTCB;
CPU_STK STEERINGSMALL_TASK_STK[STEERINGSMALL_STK_SIZE];
void steeringsmall_task(void *p_arg);


#define STEERINGEND_TASK_PRIO 15
#define STEERINGEND_STK_SIZE 128
OS_TCB SteeringendTaskTCB;
CPU_STK STEERINGEND_TASK_STK[STEERINGEND_STK_SIZE];
void steeringend_task(void *p_arg);

#define STEERINGEND2_TASK_PRIO 14
#define STEERINGEND2_STK_SIZE 128
OS_TCB Steeringend2TaskTCB;
CPU_STK STEERINGEND2_TASK_STK[STEERINGEND2_STK_SIZE];
void steeringend2_task(void *p_arg);

#define STEP1P_TASK_PRIO 8
#define STEP1P_STK_SIZE 128
OS_TCB Step1PTaskTCB;
CPU_STK STEP1P_TASK_STK[STEP1P_STK_SIZE];
void step1P_task(void *p_arg);

#define STEP1N_TASK_PRIO 8
#define STEP1N_STK_SIZE 128
OS_TCB Step1NTaskTCB;
CPU_STK STEP1N_TASK_STK[STEP1N_STK_SIZE];
void step1N_task(void *p_arg);

#define STEP2P_TASK_PRIO 8
#define STEP2P_STK_SIZE 128
OS_TCB Step2PTaskTCB;
CPU_STK STEP2P_TASK_STK[STEP2P_STK_SIZE];
void step2P_task(void *p_arg);

#define STEP2N_TASK_PRIO 8
#define STEP2N_STK_SIZE 128
OS_TCB Step2NTaskTCB;
CPU_STK STEP2N_TASK_STK[STEP2N_STK_SIZE];
void step2N_task(void *p_arg);

#define STEP3P_TASK_PRIO 8
#define STEP3P_STK_SIZE 128
OS_TCB Step3PTaskTCB;
CPU_STK STEP3P_TASK_STK[STEP3P_STK_SIZE];
void step3P_task(void *p_arg);

#define STEP3N_TASK_PRIO 8
#define STEP3N_STK_SIZE 128
OS_TCB Step3NTaskTCB;
CPU_STK STEP3N_TASK_STK[STEP3N_STK_SIZE];
void step3N_task(void *p_arg);



OS_FLAG_GRP PS2_Flags;
OS_SEM	MY_SEM;		//����һ���ź��������ڷ��ʹ�����Դ
//#define KEYMSG_Q_NUM	1	//������Ϣ���е�����
//#define DATAMSG_Q_NUM	4	//�������ݵ���Ϣ���е�����
//OS_Q KEY_Msg;				//����һ����Ϣ���У����ڰ�����Ϣ���ݣ�ģ����Ϣ����
//OS_Q DATA_Msg;				//����һ����Ϣ���У����ڷ�������

//u8 tmr1sta=0; 	//��Ƕ�ʱ���Ĺ���״̬
//OS_TMR	tmr1;	//����һ����ʱ��
//void tmr1_callback(void *p_tmr,void *p_arg); //��ʱ��1�ص�����
 
int main()
{
	OS_ERR err;
	CPU_SR_ALLOC(); //����Ĵ�����ֵ����ֹ���������� Ϊ������˳��ٽ�������һ������
	
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	LED_Init();
	
	SteppingMotor1_Initialization();
	SteppingMotor2_Initialization();
	SteppingMotor3_Initialization();
	
	SteppingMotor1_Enable();
	SteppingMotor2_Enable();
	SteppingMotor3_Enable();
	
	OSInit(&err);		//��ʼ�����ȼ������ȼ��б����������ʼ����ʱ�ӽ��������ʼ��
	OS_CRITICAL_ENTER();
	OSTaskCreate(
										(OS_TCB        *)&StartTaskTCB,
                    (CPU_CHAR      *)"start task",
                    (OS_TASK_PTR    )start_task,
                    (void          *)0,
                    (OS_PRIO        )START_TASK_PRIO,  //���ȼ�
                    (CPU_STK       *)&START_TASK_STK[0],
                    (CPU_STK_SIZE   )START_STK_SIZE/10,
                    (CPU_STK_SIZE   )START_STK_SIZE,
                    (OS_MSG_QTY     )0,     					//�ڲ���Ϣ�����ܽ��յ��������Ϣ��Ŀ��Ϊ0ʱ��֮������Ϣ
                    (OS_TICK        )0,								//ʹ��ʱ��Ƭ��ת��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ���
                    (void          *)0,								//�û�����Ĵ洢��
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //���񴴽�ѡ��
                    (OS_ERR        *)err
	);
	
	
	OS_CRITICAL_EXIT(); //�˳��ٽ���ʱ���������л�
	OSStart(&err);
	
	while(1);
	
}
 
 
 
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();	//Ϊ�����ٽ������˳��ٽ����Ĵ�������һ������
	p_arg = p_arg;
	
	CPU_Init();  		//��ʼ��CPU��ʱ������ж�...��
	#if OS_CFG_STAT_TASK_EN >0u
	OSStatTaskCPUUsageInit(&err); 	//ͳ������
	#endif
	
	#ifdef CPU_CFG_INT_DIS_MENS_EN //���ʹ���˲����жϹر�ʱ�� 
	CPU_IntDisMeasMaxCurReser();
	#endif
	
	#if OS_CFG_SCHED_ROUND_ROBIN_EN //���ʹ��ʱ��Ƭ��ת����
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
	//ʹ��ʱ��Ƭ��ת���ȣ�ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5ms
	#endif
	OS_CRITICAL_ENTER();
	
	OSSemCreate ((OS_SEM*	)&MY_SEM,
                 (CPU_CHAR*	)"MY_SEM",
                 (OS_SEM_CTR)0,		
                 (OS_ERR*	)&err);
	
	OSTaskCreate(			(OS_TCB        *)&LED0TaskTCB,
                    (CPU_CHAR      *)"led0 task",
                    (OS_TASK_PTR    )led0_task,
                    (void          *)0,
                    (OS_PRIO        )LED0_TASK_PRIO,  //���ȼ�
                    (CPU_STK       *)&LED0_TASK_STK[0],
                    (CPU_STK_SIZE   )LED0_STK_SIZE/10,
                    (CPU_STK_SIZE   )LED0_STK_SIZE,
                    (OS_MSG_QTY     )0,     					//�ڲ���Ϣ�����ܽ��յ��������Ϣ��Ŀ��Ϊ0ʱ��֮������Ϣ
                    (OS_TICK        )0,								//ʹ��ʱ��Ƭ��ת��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ���
                    (void          *)0,								//�û�����Ĵ洢��
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                    (OS_ERR        *)err	);
	
	OSTaskCreate(			(OS_TCB        *)&LED1TaskTCB,
                    (CPU_CHAR      *)"led1 task",
                    (OS_TASK_PTR    )led1_task,
                    (void          *)0,
                    (OS_PRIO        )LED1_TASK_PRIO,  
                    (CPU_STK       *)&LED1_TASK_STK[0],
                    (CPU_STK_SIZE   )LED1_STK_SIZE/10,
                    (CPU_STK_SIZE   )LED1_STK_SIZE,
                    (OS_MSG_QTY     )0,     				 
                    (OS_TICK        )0,							 
                    (void          *)0,						 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err);
										
	OSTaskCreate(			(OS_TCB        *)&PS2TaskTCB,
                    (CPU_CHAR      *)"ps2 task",
                    (OS_TASK_PTR    )ps2_task,
                    (void          *)0,
                    (OS_PRIO        )PS2_TASK_PRIO,   
                    (CPU_STK       *)&PS2_TASK_STK[0],
                    (CPU_STK_SIZE   )PS2_STK_SIZE/10,
                    (CPU_STK_SIZE   )PS2_STK_SIZE,
                    (OS_MSG_QTY     )0,     				 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err);
	
		OSTaskCreate(		(OS_TCB        *)&SteeringupTaskTCB,
                    (CPU_CHAR      *)"steeringup task",
                    (OS_TASK_PTR    )steeringup_task,
                    (void          *)0,
                    (OS_PRIO        )STEERINGUP_TASK_PRIO,  
                    (CPU_STK       *)&STEERINGUP_TASK_STK[0],
                    (CPU_STK_SIZE   )STEERINGUP_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEERINGUP_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
		OSTaskCreate(		(OS_TCB        *)&SteeringdownTaskTCB,
                    (CPU_CHAR      *)"steeringdown task",
                    (OS_TASK_PTR    )steeringdown_task,
                    (void          *)0,
                    (OS_PRIO        )STEERINGDOWN_TASK_PRIO,  
                    (CPU_STK       *)&STEERINGDOWN_TASK_STK[0],
                    (CPU_STK_SIZE   )STEERINGDOWN_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEERINGDOWN_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
		OSTaskCreate(		(OS_TCB        *)&SteeringsmallTaskTCB,
                    (CPU_CHAR      *)"steeringsmall task",
                    (OS_TASK_PTR    )steeringsmall_task,
                    (void          *)0,
                    (OS_PRIO        )STEERINGSMALL_TASK_PRIO,  
                    (CPU_STK       *)&STEERINGSMALL_TASK_STK[0],
                    (CPU_STK_SIZE   )STEERINGSMALL_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEERINGSMALL_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
										
		OSTaskCreate(		(OS_TCB        *)&SteeringendTaskTCB,
                    (CPU_CHAR      *)"steeringend task",
                    (OS_TASK_PTR    )steeringend_task,
                    (void          *)0,
                    (OS_PRIO        )STEERINGEND_TASK_PRIO,  
                    (CPU_STK       *)&STEERINGEND_TASK_STK[0],
                    (CPU_STK_SIZE   )STEERINGEND_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEERINGEND_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
		OSTaskCreate(		(OS_TCB        *)&Steeringend2TaskTCB,
                    (CPU_CHAR      *)"steeringend2 task",
                    (OS_TASK_PTR    )steeringend2_task,
                    (void          *)0,
                    (OS_PRIO        )STEERINGEND2_TASK_PRIO,  
                    (CPU_STK       *)&STEERINGEND2_TASK_STK[0],
                    (CPU_STK_SIZE   )STEERINGEND2_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEERINGEND2_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )0,						 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);	
		 OSFlagCreate ( (OS_FLAG_GRP  *)&PS2_Flags,
                    (CPU_CHAR     *)"PS2 Flags",
                    (OS_FLAGS      )0x00,
                    (OS_ERR       *)err);
								

		OSTaskCreate(		(OS_TCB        *)&Step1PTaskTCB,
                    (CPU_CHAR      *)"step1P task",
                    (OS_TASK_PTR    )step1P_task,
                    (void          *)0,
                    (OS_PRIO        )STEP1P_TASK_PRIO, 
                    (CPU_STK       *)&STEP1P_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP1P_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP1P_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,								 
                    (void          *)0,						 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
		OSTaskCreate(		(OS_TCB        *)&Step1NTaskTCB,
                    (CPU_CHAR      *)"step1N task",
                    (OS_TASK_PTR    )step1N_task,
                    (void          *)0,
                    (OS_PRIO        )STEP1N_TASK_PRIO,  
                    (CPU_STK       *)&STEP1N_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP1N_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP1N_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,							 
                    (void          *)0,								 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
			OSTaskCreate(		(OS_TCB        *)&Step2PTaskTCB,
                    (CPU_CHAR      *)"step2P task",
                    (OS_TASK_PTR    )step2P_task,
                    (void          *)0,
                    (OS_PRIO        )STEP2P_TASK_PRIO,   
                    (CPU_STK       *)&STEP2P_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP2P_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP2P_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,								 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
			OSTaskCreate(		(OS_TCB        *)&Step2NTaskTCB,
                    (CPU_CHAR      *)"step2N task",
                    (OS_TASK_PTR    )step2N_task,
                    (void          *)0,
                    (OS_PRIO        )STEP2N_TASK_PRIO,  
                    (CPU_STK       *)&STEP2N_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP2N_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP2N_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,							 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
			OSTaskCreate(		(OS_TCB        *)&Step3PTaskTCB,
                    (CPU_CHAR      *)"step3P task",
                    (OS_TASK_PTR    )step3P_task,
                    (void          *)0,
                    (OS_PRIO        )STEP3P_TASK_PRIO,   
                    (CPU_STK       *)&STEP3P_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP3P_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP3P_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,								 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
			OSTaskCreate(		(OS_TCB        *)&Step3NTaskTCB,
                    (CPU_CHAR      *)"step3N task",
                    (OS_TASK_PTR    )step3N_task,
                    (void          *)0,
                    (OS_PRIO        )STEP3N_TASK_PRIO,  
                    (CPU_STK       *)&STEP3N_TASK_STK[0],
                    (CPU_STK_SIZE   )STEP3N_STK_SIZE/10,
                    (CPU_STK_SIZE   )STEP3N_STK_SIZE,
                    (OS_MSG_QTY     )0,     					 
                    (OS_TICK        )3,							 
                    (void          *)0,							 
                    (OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                    (OS_ERR        *)err	);
										
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);
	OS_CRITICAL_EXIT();
	
}
 
 
void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		LED0=~LED0;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_NON_STRICT,&err); 
	}
}
 
  
void led1_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		LED1=0;
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_NON_STRICT,&err); //opt��ʾ�����趨��ʱ�䣨�ϸ�/���ϸ�
		LED1=1;
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_NON_STRICT,&err);
	}
}
 
 
void ps2_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	uint8_t key = 0;
	ps2_init();
	ps2_gpio_init();
	PS2_SetInit();
	PS2_Vibration(0x01,0xFF);
	OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_HMSM_NON_STRICT,&err);
	
	while(1)
	{
		key = PS2_DataKey();
		if (key == 0x05)
		{
			OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x05)
			{		
			//OSSemPost(&MY_SEM,OS_OPT_POST_1,&err);
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x01,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
		else if( key == 0x07 )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x07)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x02,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x06 )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x06)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x04,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x08 )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x08)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x08,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x0D )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0D)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x10,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x0F )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0F)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x20,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x09 )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x09)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x40,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x0A )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0A)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x80,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
				else if( key == 0x0B )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0B)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x200,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
		
				else if( key == 0x0C )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0C)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x400,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}		
		else if( key == 0x0E )
		{
				OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);			
				if (PS2_DataKey() == 0x0E)
			{		
			OS_FlagPost (		 (OS_FLAG_GRP  *)&PS2_Flags,
                       (OS_FLAGS      )0x800,
                       (OS_OPT        )OS_OPT_POST_FLAG_SET,
                       (CPU_TS        )NULL,
                       (OS_ERR       *)&err);
			}
		}
		
		
		OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_NON_STRICT,&err);
		if(PS2_Flag == 1)
			PS2Send(key);
	}
}
 
void steeringup_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	SteeringEngine1_Initialization();
	SteeringEngine2_Initialization();
	SteeringEngine3_Initialization();
	SteeringEngine10_Initialization();
//	TIM14_PWM_Init(2000-1,84-1); //PA7
//	TIM13_PWM_Init(2000-1,84-1); //PA6
//TIM12_PWM_Init(2000-1,84-1); //CH1PB14 CH2PB15
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x40,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
 
	//	TIM_SetCompare1(TIM14,400);
		SteeringEngine1_SetAngle(160); //175
		delay_ms(500);
		SteeringEngine3_SetAngle(0);
		
		SteeringEngine10_SetAngle(90);
		delay_ms(500);
		SteeringEngine4_SetAngle(90); //suck
		

		delay_ms(500);
		SteeringEngine2_SetAngle(5); //pole
		delay_ms(500);
		//printf("up\n");
	}

}


void steeringdown_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	

	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x80,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
//		 SteeringEngine3_SetAngle(90); //under open
//		delay_ms(100);
		SteeringEngine4_SetAngle(0); //suck
		delay_ms(200);
	 
		SteeringEngine10_SetAngle(0); //up close
		delay_ms(200);
    SteeringEngine3_SetAngle(0); //under close
		SteeringEngine2_SetAngle(90); //pole
		delay_ms(500);
		//SteeringEngine3_SetAngle(0); //under close
	//	delay_ms(500);
	//	delay_ms(100);
		SteeringEngine1_SetAngle(55);
	//	printf("down\n");	
	}

}

void steeringsmall_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x400,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteeringEngine1_SetAngle(165);
		delay_ms(500);
		
	  SteeringEngine3_SetAngle(90); //under open
		SteeringEngine10_SetAngle(0); //up close
		SteeringEngine4_SetAngle(68); //suck

		delay_ms(500);

		SteeringEngine2_SetAngle(10); //pole
		delay_ms(500);
	
		//printf("down\n");	
	}

}

void steeringend_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x200,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		
		SteeringEngine1_SetAngle(55);		
		SteeringEngine3_SetAngle(0);  //close 
		SteeringEngine10_SetAngle(90); //close
		
		printf("end\n");

	}

}

void steeringend2_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x800,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
			SteeringEngine1_SetAngle(55);		
		SteeringEngine3_SetAngle(90);  //open
		SteeringEngine10_SetAngle(0); //open
		
		printf("end\n");

	}

}
 
void step1P_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x01,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor1_Turn(-10);
		 OSSched();
	}
	
	
	
}

void step1N_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x02,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor1_Turn(10);
		 OSSched();
	}
}


void step2P_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	

	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x04,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor3_Turn(5);
		 OSSched();
	}
	
	
	
}

void step2N_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x08,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor3_Turn(-5);
		 OSSched();
	}
}

void step3P_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	

	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x10,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor2_Turn(-10);
		 OSSched();
	}
	
	
	
}

void step3N_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		OSFlagPend (		(	OS_FLAG_GRP  *)&PS2_Flags,
                    ( OS_FLAGS      )0x20,
                    ( OS_TICK       )0,
                    ( OS_OPT        )OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME + OS_OPT_PEND_BLOCKING,
                    ( CPU_TS       *)NULL,
                    ( OS_ERR       *)&err);
		SteppingMotor2_Turn(10);
		 OSSched();
	}
}














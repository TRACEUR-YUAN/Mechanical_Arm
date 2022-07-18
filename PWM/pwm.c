#include "pwm.h"
#include "led.h"
#include "usart.h"
 

//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); //GPIOF9����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM14
 
										  
}  


void TIM13_PWM_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	   
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13 );
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=arr;  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure); 
	
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);   

	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  
 
  TIM_ARRPreloadConfig(TIM13,ENABLE);  
	
	TIM_Cmd(TIM13, ENABLE);  
	
	
}


void TIM12_PWM_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	   
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM13 );
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM13 );
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB ,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=arr;  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure); 
	
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);   

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  
	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);  
	
	TIM_Cmd(TIM12, ENABLE);  
	
	
}


//void TIM11_PWM_Init(u32 arr,u32 psc)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM11,ENABLE);  	   
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 

//	GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM13 );
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOF ,&GPIO_InitStructure);
//	
//	TIM_TimeBaseStructure.TIM_Prescaler=psc; 
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//	TIM_TimeBaseStructure.TIM_Period=arr;  
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure); 
//	
// 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
//	TIM_OC1Init(TIM13, &TIM_OCInitStructure);   

//	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  
// 
//  TIM_ARRPreloadConfig(TIM13,ENABLE);  
//	
//	TIM_Cmd(TIM13, ENABLE);  
//	
//	
//}



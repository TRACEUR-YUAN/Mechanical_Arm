#ifndef _PS2_H_
#define _PS2_H_

#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"

#define DI   PBin(12)           //PB12  ����

#define DO_H PBout(13)=1        //����λ��
#define DO_L PBout(13)=0        //����λ��

#define CS_H PBout(14)=1       //CS����
#define CS_L PBout(14)=0       //CS����

#define CLK_H PBout(15)=1      //ʱ������
#define CLK_L PBout(15)=0      //ʱ������


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2         9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //��ҡ��X������
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8



void ps2_init(void);
void ps2_gpio_init(void);
u8 PS2_RedLight(void);//�ж��Ƿ�Ϊ���ģʽ
void PS2_ReadData(void);
void PS2_Cmd(u8 CMD);		  //
u8 PS2_DataKey(void);		  //��ֵ��ȡ
u8 PS2_AnologData(u8 button); //�õ�һ��ҡ�˵�ģ����
void PS2_ClearData(void);	  //������ݻ�����

void PS2_Config(void);
void PS2_EnterConfig(void);
void PS2_TurnOnAnalogMode(void);
void PS2_VibrationMode(void);
void PS2_VibrationMode(void);
void PS2_SetInit(void);
void PS2_Vibration(u8 motor1,u8 motor2);
void PS2Send(u8 key);

#endif






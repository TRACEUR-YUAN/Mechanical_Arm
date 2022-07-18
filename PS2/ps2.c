#include "ps2.h"

u16 Handkey;
u8 Comd[2]={0x01,0x42};	//��ʼ�����������
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //���ݴ洢����
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//����ֵ�밴����



void ps2_init(void)
{
   
	GPIO_InitTypeDef GPIO_PS2;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_PS2.GPIO_Pin = GPIO_Pin_12;
	GPIO_PS2.GPIO_Mode = GPIO_Mode_IN;
	GPIO_PS2.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&GPIO_PS2);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	

}	

void ps2_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_PS2_1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_PS2_1.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_PS2_1.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_PS2_1.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB,&GPIO_PS2_1);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);	
}




//���ֱ���������
void PS2_Cmd(u8 CMD)
{
	volatile u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //�����Ϊ����λ
		}
		else DO_L;

		CLK_H;                        //ʱ������
		delay_us(5);
		CLK_L;
		delay_us(5);
		CLK_H;
		if(DI)
			Data[1] = ref|Data[1];
	}
	delay_us(16);
}


//�ж��Ƿ�Ϊ���ģʽ
//����ֵ��0�����ģʽ
//����������ģʽ
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //��ʼ����
	PS2_Cmd(Comd[1]);  //��������
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;

}

//��ȡ�ֱ�����
void PS2_ReadData(void)
{
	volatile u8 byte=0;
	volatile u16 ref=0x01;

	CS_L;

	PS2_Cmd(Comd[0]);  //��ʼ����
	PS2_Cmd(Comd[1]);  //��������

	for(byte=2;byte<9;byte++)          //��ʼ��������
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			delay_us(5);
			CLK_L;
			delay_us(5);
			CLK_H;
		      if(DI)
		      Data[byte] = ref|Data[byte];
		}
        delay_us(16);
	}
	CS_H;	
}


//�Զ�������PS2�����ݽ��д���     
//ֻ�����˰�������         
//Ĭ�������Ǻ��ģʽ  ֻ��һ����������ʱ
//����Ϊ0�� δ����Ϊ1
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //����16������  ����Ϊ0�� δ����Ϊ1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //û���κΰ�������
}



//�õ�һ��ҡ�˵�ģ����	 ��Χ0~256
//���ģʽ����Ч
//��Щֵ�洢��Data[5]��Data[6]��Data[7]��Data[8]
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//������ݻ�����
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}


/*�ֱ����ã�����Ҫ�����ֱ����ظ���������Ϣ*/


//�ֱ����ó�ʼ����
void PS2_Config(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x42);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	delay_us(16);
}

//��������
void PS2_EnterConfig(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x43);
	PS2_Cmd(0x00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	delay_us(16);
}

//����ģʽ����
void PS2_TurnOnAnalogMode(void)
{
	CS_L;
	PS2_Cmd(0x01);
	PS2_Cmd(0x44);
	PS2_Cmd(0x00);
	PS2_Cmd(0x01); //analog = 0x01, digital = 0x00
	PS2_Cmd(0xEE); //03�������� EE������
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	delay_us(16);	
}

//��ģʽ
void PS2_VibrationMode(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x4D);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x01);
	CS_H;
	delay_us(16);
}

//��ɲ���������
void PS2_ExitConfig(void)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x43);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	delay_us(16);
}

//�ֱ�����
void PS2_SetInit(void)
{
	PS2_Config();
	PS2_Config();
	PS2_Config();
	PS2_EnterConfig();
	PS2_TurnOnAnalogMode();
	PS2_VibrationMode();
	PS2_ExitConfig();
}



void PS2_Vibration(u8 motor1,u8 motor2)
{
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);
	PS2_Cmd(0x42);
	PS2_Cmd(0x00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
 	CS_H;
	delay_us(16);
}


void PS2Send(u8 key)
{
		switch(key)
								{
									case 5:
										printf("%c",0x05); break;
									case 6:
										printf("%c",0x06); break;
									case 7:
										printf("%c",0x07); break;
									case 8:
										printf("%c",0x08);break;
									case 13:
										printf("%c",0x0d);break;
									case 14:
										printf("%c",0x0e);break;
									case 15:
										printf("%c",0x0f);break;
									case 16:
										printf("%c",0x10);break;
									default: break;
								}
}







































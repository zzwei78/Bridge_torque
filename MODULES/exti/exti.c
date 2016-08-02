#include "exti.h"
#include "spi.h"
#include "ads1258.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

int Count=0;
extern u8 Sign_Flag;

void EXTI_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
		
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource8);
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line8;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
		NVIC_Init(&NVIC_InitStructure);	
}

void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
    {
        if(START==1)
        {
            if(Count<16)
            {
                ads1258_ReadData();
                Count++;
            }
            else
            {
                START=0;
                Count=0;
                convert_AD_RawData();
                USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
                Save_AD_RawData();//to save Data
            }
        }
		EXTI_ClearITPendingBit(EXTI_Line8);
    }
}

void EXTI_Sign_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
		GPIO_Init(GPIOF,&GPIO_InitStructure);
		
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,EXTI_PinSource2);
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line2;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
		NVIC_Init(&NVIC_InitStructure);	
}

void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
    {
        Sign_OUT=1;
        Sign_Flag=1 ;
        START=1;
		EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

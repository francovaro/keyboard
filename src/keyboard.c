/*
 *  @file  : keyboard.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 nov 2019
 */
/* STM include*/
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"

#include <stdint.h>

#include "keyboard.h"

static void keyboard_SetFunctionality(void);
static t_keyboard keyboard[eKey_LAST];

/**
 * @brief
 */
void Keyboard_StartCheck(void)
{

}

/**
 * @brief
 */
void Keyboard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	pressedGlobal = 0;

	/* init clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);	/* useful ? */

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/*--------------------------------------------------------------------------------------*/
	/* GPIO Init */
	/* init GPIO as input */
	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource11);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource12);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource13);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource14);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);


	/*--------------------------------------------------------------------------------------*/
	/* EXTINT Init */
	/* set ext  10 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		/* yeah rising or falling ? */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* set ext  11 to 15 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_Init(&EXTI_InitStructure);

	/*--------------------------------------------------------------------------------------*/
	/* INTERRUPT Init */
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	keyboard_SetFunctionality();
}

void EXTI15_10_IRQHandler(void)
{
	uint8_t i;

	for (i = 0; i< eKey_LAST; i++)
	{
		if (EXTI_GetITStatus(keyboard[i].intLine) == SET)
		{
			EXTI_ClearITPendingBit(keyboard[i].intLine);
			//pressedGlobal = pressedGlobal | (1 << keyboard[i].key);
			if (GPIO_ReadInputDataBit(keyboard[i].port, keyboard[i].pin) == RESET)
			{
				pressedGlobal |= (1 << keyboard[i].key);	/* let's xor it */
			}
			else
			{
				pressedGlobal &= (~(1 << keyboard[i].key));	/* let's xor it */
			}


		}
	}

}

void keyboard_SetFunctionality(void)
{
	uint8_t i;

	for (i = 0; i < eKey_LAST ; i++)
	{
		keyboard[i].func = (void*)0;
		keyboard[i].key = (eKeyboard_key)i;
	}

	keyboard[0].port = GPIOA;
	keyboard[0].pin	= GPIO_Pin_10;
	keyboard[0].intLine = EXTI_Line10;

	keyboard[1].port = GPIOA;
	keyboard[1].pin	= GPIO_Pin_11;
	keyboard[1].intLine = EXTI_Line11;

	keyboard[2].port = GPIOA;
	keyboard[2].pin	= GPIO_Pin_12;
	keyboard[2].intLine = EXTI_Line12;

	keyboard[3].port = GPIOA;
	keyboard[3].pin	= GPIO_Pin_13;
	keyboard[3].intLine = EXTI_Line13;

	keyboard[4].port = GPIOA;
	keyboard[4].pin	= GPIO_Pin_14;
	keyboard[4].intLine = EXTI_Line14;

	keyboard[5].port = GPIOA;
	keyboard[5].pin	= GPIO_Pin_15;
	keyboard[5].intLine = EXTI_Line15;
}

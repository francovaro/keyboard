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
#include "stm32f4xx_exti.h"

#include <stdint.h>

#include "keyboard.h"

static void keyboard_SetFunctionality(void);
static t_keyboard keyboard[eKey_LAST];

void Keyboard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	pressed_11 = RESET;
	pressed_12 = RESET;

	/* init clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);	/* useful ? */

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/* init GPIO as input */
	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_12 | GPIO_Pin_11);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource12);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource11);

	/* set ext  12 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* set ext  11 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);

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
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{
		/* Clear the EXTI line 12 pending bit */
		pressed_11 = SET;

		EXTI_ClearITPendingBit(EXTI_Line11);
	}

	if(EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		/* Clear the EXTI line 12 pending bit */
		pressed_12 = SET;

		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}

void keyboard_SetFunctionality(void)
{
	keyboard[0].func = (void*)0;
	keyboard[0].key = eKey_OK;
	keyboard[0].port = GPIOA;
	keyboard[0].pin	= GPIO_Pin_11;
	keyboard[0].intLine = EXTI_Line11;

	keyboard[1].func = (void*)0;
	keyboard[1].key = eKey_CANCEL;
	keyboard[1].port = GPIOA;
	keyboard[1].pin	= GPIO_Pin_12;
	keyboard[1].intLine = EXTI_Line12;
}

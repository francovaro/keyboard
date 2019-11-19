/*
 * systick.c
 *
 *  Created on: 28 ott 2019
 *      Author: franc
 */

#include "stm32f4xx.h"
#include "systick.h"
#include "keyboard.h"


#define PRESS_THRESHOLD		(5u)	/* in ms*/

void Systick_set(uint32_t timeMs)
{
	 RCC_ClocksTypeDef RCC_Clocks;
	 RCC_GetClocksFreq(&RCC_Clocks);
	 SysTick_Config(RCC_Clocks.HCLK_Frequency/timeMs); // hz/s

	 systick_pressed = 0;
}

void SysTick_Handler(void)
{
	static uint16_t counter[eKey_LAST] = {0};
	uint8_t i;

	for( i = 0; i < eKey_LAST; i++)
	{
		if (pressedGlobal & (1<<i))
		{
			counter[i]++;
			if (counter[i] > PRESS_THRESHOLD)
			{
				systick_pressed |= (1<<i);	/* set it */
			}
		}
		else
		{
			counter[i] = 0;
			systick_pressed &= (~(1<<i));	/*	clear it */
		}
	}

}

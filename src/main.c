/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>

#include "keyboard.h"
#include "uart.h"
#include "systick.h"
			

int main(void)
{
	static uint16_t localPressed = 0;
	uint16_t i;
	char * start 		= "START\n";
	char toSend[20];

	Systick_set(100);
	Keyboard_Init();
	UART_fv_config(RESET);

	UART_fv_SendData(start, strlen(start));

	while(1)
	{

		if (localPressed != systick_pressed)
		{
			for( i = 0; i < eKey_LAST; i++)
			{
				if ( (pressedGlobal & (1<<i)) != (localPressed& (1<<i)) )
				{
					snprintf(toSend, sizeof(toSend), "%d\n", pressedGlobal);
					UART_fv_SendData(toSend, strlen(toSend));
				}
			}

			localPressed = systick_pressed;
		}

	}

}

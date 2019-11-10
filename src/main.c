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

#include "keyboard.h"
#include "uart.h"
			

int main(void)
{
	uint16_t i;
	const char * start 		= "START\n";

	Keyboard_Init();
	UART_fv_config(RESET);

	UART_fv_SendData(start, strlen(start));

	while(1)
	{
		if (pressedGlobal != 0)
		{
			for( i = 0; i < eKey_LAST; i++)
			{
				if (pressedGlobal & (1<<i))
				{
					pressedGlobal^= (1<<i);
				}
			}


		}
	}

}

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
	const char * print_11 	= "11\n";
	const char * print_12 	= "12\n";
	const char * start 		= "START\n";

	Keyboard_Init();
	UART_fv_config(RESET);

	UART_fv_SendData(start, strlen(start));

	while(1)
	{
		if (pressed_11 == SET)
		{
			pressed_11 = RESET;
			UART_fv_SendData(print_11, strlen(print_11));
		}

		if (pressed_12 == SET)
		{
			pressed_12 = RESET;
			UART_fv_SendData(print_12, strlen(print_12));
		}
	}

}

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

#include "keyboard.h"
			

int main(void)
{
	keyboard_Init();

	while(1)
	{
		if (pressed == SET)
		{
			pressed = RESET;
		}

	}

}

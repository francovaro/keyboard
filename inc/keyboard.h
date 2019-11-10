/*
 *  @file  : keyboard.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 10 nov 2019
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "stm32f4xx_gpio.h"

volatile uint8_t pressed_11;
volatile uint8_t pressed_12;

typedef enum
{
	eKey_UP,
	eKey_DOWN,
	eKey_LEFT,
	eKey_RIGHT,
	eKey_OK,
	eKey_CANCEL,
	eKey_LAST,
} eKeyboard_key;

/**
 * pin
 * functionality
 * function ?
 */
typedef struct
{
	uint32_t 			pin;
	uint32_t			intLine;
	GPIO_TypeDef*		port;
	eKeyboard_key 		key;
	void (*func) (void);
}t_keyboard;


void keyboard_Init(void);


#endif /* KEYBOARD_H_ */

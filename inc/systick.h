/*
 * systick.h
 *
 *  Created on: 28 ott 2019
 *      Author: franc
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

volatile uint16_t systick_pressed;

extern void Systick_set(uint32_t timeMs);

#endif /* SYSTICK_H_ */

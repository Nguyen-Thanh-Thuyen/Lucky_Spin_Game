/*
 * display_7SEG.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_DISPLAY_7SEG_H_
#define INC_DISPLAY_7SEG_H_

#include "main.h"
#include "global.h"



extern const uint8_t SEG_CC[10];


uint8_t invert_byte(uint8_t x);

void clk_pulse(void);
void latch_pulse(void);
void shift_byte(uint8_t data);
void HC595_Send3_GPIO(uint8_t b3, uint8_t b2, uint8_t b1);
void update_led_buffer(int num1, int num2, int num3);
void display_3_digit();

#endif /* INC_DISPLAY_7SEG_H_ */

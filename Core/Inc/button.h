/*
 * button.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_BUTTONS 10

// STRUCT

typedef struct {
    int KeyReg0;
    int KeyReg1;
    int KeyReg2;
    int KeyReg3;

    int TimeOutForKeyPress;

    int flag_pressed;
    int flag_long_pressed;
    int flag_released; // new attribute
} Button_t;

// API

void Button_Init();
void getKeyInput();

void subKeyProcess(int index);
void setButtonFlag(int index);
int isButtonPressed(int index);
int isButtonLongPressed(int index);
int isButtonReleased(int index);



#endif /* INC_BUTTON_H_ */

/*
 * buzzer.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "global.h"
#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef htim1;
typedef struct {
    char *name;
    float freq;
} NoteFreq;


uint32_t GetARR(char *noteName);
void PlayNote(char *noteName, uint16_t duration, uint8_t volumePercent);
void PlayJackpotTune();
void PlaySadLoseTune();
void PlayWelcomeTune();
#endif /* INC_BUZZER_H_ */

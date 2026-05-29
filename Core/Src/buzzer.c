/*
 * buzzer.c
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#include "main.h"
#include "global.h"
#include "buzzer.h"
#include <string.h>


// Bảng tần số các nốt nhạc


NoteFreq notes[] = {
    {"C4", 261.63}, {"D4", 293.66}, {"E4", 329.63}, {"F4", 349.23},
    {"G4", 392.00}, {"A4", 440.00}, {"B4", 493.88}, {"C5", 523.25},
    {"D5", 587.33}, {"E5", 659.25}, {"F5", 698.46}, {"G5", 783.99},
    {"A5", 880.00}, {"B5", 987.77}, {"C6", 1046.50}
};


// Hàm tìm ARR từ tên nốt
uint32_t GetARR(char *noteName) {
    for (int i = 0; i < sizeof(notes)/sizeof(notes[0]); i++) {
        if (strcmp(notes[i].name, noteName) == 0) {
            return (uint32_t)(1000000.0 / notes[i].freq) - 1; // Timer chạy 1 MHz
        }
    }
    return 0; // Nếu không tìm thấy
}

// Hàm phát nốt nhạc với tham số volume (0–100%)
void PlayNote(char *noteName, uint16_t duration, uint8_t volumePercent) {
    uint32_t arr = GetARR(noteName);
    if (arr == 0) return; // Không hợp lệ

    htim1.Init.Prescaler = 7;        // 8 MHz / (7+1) = 1 MHz
    htim1.Init.Period = arr;
    HAL_TIM_PWM_Init(&htim1);

    // Duty cycle theo phần trăm âm lượng
    uint32_t compare = (arr * volumePercent) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compare);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_Delay(duration);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

    HAL_Delay(50); // nghỉ ngắn giữa các nốt
}


void PlayJackpotTune() {
    PlayNote("C4", 100, 30);
    PlayNote("E4", 100, 35);
    PlayNote("G4", 100, 40);

    PlayNote("C5", 120, 45);
    PlayNote("E5", 120, 50);
    PlayNote("G5", 120, 55);

    PlayNote("C6", 600, 70);
    HAL_Delay(100);
    PlayNote("C6", 900, 75);   // nổ lần 2
}

void PlaySadLoseTune() {
    PlayNote("C5", 200, 35);
    PlayNote("B4", 200, 30);
    PlayNote("A4", 200, 30);
    PlayNote("G4", 300, 25);
    PlayNote("E4", 900, 20);
}

void PlayWelcomeTune() {
    PlayNote("C4", 200, 30);
    PlayNote("E4", 200, 35);
    PlayNote("G4", 200, 40);
    PlayNote("E4", 200, 35);
    PlayNote("C5", 500, 45);
}

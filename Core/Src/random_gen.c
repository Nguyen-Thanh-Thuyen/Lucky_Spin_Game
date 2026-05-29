/*
 * random_gen.c
 *
 *  Created on: Mar 15, 2026
 *      Author: thuyen
 */


#include "random_gen.h"
#include "main.h"

extern ADC_HandleTypeDef hadc1;

static uint32_t seed = 1;

// Hàm đọc ADC 1 lần
static uint16_t adc_read() {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    uint16_t val = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return val;
}

void random_init() {
    // 1. Lấy nhiễu ADC (pin để floating hoặc nối cảm biến)
    uint16_t adcVal = adc_read();

    // 2. Lấy entropy bổ sung từ SysTick
    uint32_t timeNoise = HAL_GetTick();

    // 3. Khởi tạo seed
    seed = (adcVal << 16) | (timeNoise & 0xFFFF);

    if (seed == 0) seed = 1; // tránh seed = 0
}

// PRNG kiểu LCG
static uint32_t random32() {
    seed = (1103515245 * seed + 12345);
    return (seed >> 16);
}

// Trả về số 0–9
int random_digit() {
    return random32() % 10;
}

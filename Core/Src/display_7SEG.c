/*
 * display_7SEG.c
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */


#include "display_7SEG.h"

int index_led = 0;
//int led_buffer[MAX_LED] = {1, 2, 3};

const uint8_t SEG_CC[10] = {
    0x3F, // 0: a b c d e f
    0x06, // 1: b c
    0x5B, // 2: a b d e g
    0x4F, // 3: a b c d g
    0x66, // 4: b c f g
    0x6D, // 5: a c d f g
    0x7D, // 6: a c d e f g
    0x07, // 7: a b c
    0x7F, // 8: a b c d e f g
    0x6F  // 9: a b c d f g
};

void clk_pulse(void) {
    HAL_GPIO_WritePin(SDK_GPIO_Port, SDK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SDK_GPIO_Port, SDK_Pin, GPIO_PIN_RESET);
}

void latch_pulse(void) {
    HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET);
}

void shift_byte(uint8_t data) {
    for (int i = 7; i >= 0; --i) { // MSB trước
        HAL_GPIO_WritePin(SDO_GPIO_Port, SDO_Pin, (data & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        clk_pulse();
    }
}

void HC595_Send3_GPIO(uint8_t b3, uint8_t b2, uint8_t b1) {
    HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET);

    shift_byte(b3);
    shift_byte(b2);
    shift_byte(b1);

    latch_pulse();
}

uint8_t invert_byte(uint8_t x) {
    return (~x) & 0x7F; // chỉ 7 bit a..g, giữ DP = 0 nếu cần
}

void update_led_buffer(int num1, int num2, int num3){
	led_buffer[0] = num1;
	led_buffer[1] = num2;
	led_buffer[2] = num3;
}

void display_3_digit(void) {
    uint8_t b1 = SEG_CC[led_buffer[0]];
    uint8_t b2 = SEG_CC[led_buffer[1]];
    uint8_t b3 = SEG_CC[led_buffer[2]];

    // Gửi theo thứ tự U1 → U2 → U3
    HC595_Send3_GPIO(invert_byte(b3), invert_byte(b2), invert_byte(b1) );
}

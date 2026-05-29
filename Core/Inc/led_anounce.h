/*
 * led_anounce.h
 *
 *  Created on: Dec 12, 2026
 *      Author: thuyen
 */

#ifndef INC_LED_ANOUNCE_H_
#define INC_LED_ANOUNCE_H_


#include "main.h"
#include "software_timer.h"
#include "global.h"

// Các trạng thái máy trạng thái
#define LED_STATE_IDLE 	0
#define LED_STATE_ON   	1
#define LED_STATE_OFF  	2

// Các mục tiêu nhấp nháy
#define TARGET_NONE  	0
#define TARGET_GREEN 	1 //win / player 1
#define TARGET_RED   	2 //lose / player 2
#define TARGET_BOTH  	3 // draw


// Hàm khởi tạo
void Led_Announce_Init(void);

// Các hàm kích hoạt hiệu ứng
void Led_BlinkGreen(void); // Dùng cho P1 thắng hoặc Win game 1 người
void Led_BlinkRed(void);   // Dùng cho P2 thắng hoặc Thua game 1 người
void Led_BlinkBoth(void);  // Dùng cho Hoà (Draw)

// Hàm xử lý chính
void Led_Announce_Process(void);


#endif /* INC_LED_ANOUNCE_H_ */

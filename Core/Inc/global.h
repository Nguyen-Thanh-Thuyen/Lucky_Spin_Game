/*
 * global.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "button.h"
#include "display_7SEG.h"
#include "display_LCD.h"
#include "main.h"
#include "random_gen.h"
#include "software_timer.h"
#include "mode_single_spin.h"
#include "mode_accel_decel_spin.h"
#include "mode_hold_spin.h"
#include "mode_two_players.h"
#include "logic_game.h"


#define INIT					0
#define MODE_SINGLE_SPIN		1
#define MODE_HOLD_SPIN			2
#define MODE_ACCEL_DECEL_SPIN	3
#define MODE_TWO_PLAYERS		4
#define LIST_MODES				5
#define WELCOME_SCREEN			6
#define HOME_SCREEN				7

#define ERROR					99
#define MAX_LED 	3

extern int status;
extern int status_temp;
extern int choose_mode;

extern int led_buffer[MAX_LED];
extern int last_time;
extern int spin_flag;




//TIMER INDEX
//define timer role
#define TIMER_LED_BLINKY		0	// 1000ms
#define TIMER_LOGIC_GAME		1	// 10ms
#define SPIN					2	// 100ms - display speed 7SEG normal case
#define TIMER_SPIN_ID  			3	// speed ms - display speed 7SEG accel decel case
#define TIMER_ACCEL_ID 			4	// 100ms - duration change speed
#define TIMER_WAIT_RESULT 		5 	// 2000ms - wait time to display result in mode 2 players
#define TIMER_LCD_ANIMATION     6  // animation in spinning
#define WAIT_SCREEN_2P			7	// 1000ms - wait time to display "Two Players"
#define LED_TIMER_ID 			8
#define TIMER_BLINK				9



//define cycle for timer interrupt
#define BLINK_CYCLE				250
#define LCD_UPDATE_CYCLE        200 // Cập nhật LCD mỗi 200ms (5 khung hình/giây)


#define BLINK_DURATION 			100
#define BLINK_TIMES    			3

#endif /* INC_GLOBAL_H_ */

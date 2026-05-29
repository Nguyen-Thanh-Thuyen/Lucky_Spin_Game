/*
 * display_LCD.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_DISPLAY_LCD_H_
#define INC_DISPLAY_LCD_H_

#include "i2c_lcd.h"
#include "global.h"

// Vùng chạy trên LCD 20x4
#define RUN_COL_START   2
#define RUN_COL_END     17
#define RUN_LEN         (RUN_COL_END - RUN_COL_START + 1)
#define ARROW_LEN 3   // "<<<" hoặc ">>>"

//define announcement
#define START					20
#define BIGWIN					21
#define BETTER_LUCK_NEXT_TIME	22
#define P1_LOSE					23
#define P2_LOSE					24
#define TIE						25




void display_init();
void display_welcome_screen();
void display_announcement(int);
void display_while_playing();
void display_list_button();
void reset_animation_pos();

// advanced

void display_list_modes();
void display_mode_two_players(int index_player);

#endif /* INC_DISPLAY_LCD_H_ */

/*
 * mode_accel_decel_spin.c
 *
 *  Created on: Apr 9, 2026
 *      Author: thuyen
 */


#include "mode_accel_decel_spin.h"
#include "button.h"
#include "global.h"
#include "software_timer.h"
#include "display_7SEG.h"
#include "display_LCD.h"
#include "random_gen.h"
#include "led_anounce.h"
#include "buzzer.h"
//#include "logic_game.h"



int temp_accel_decel_spin = 0;
int speed = 500;
int check = 0;
int speed_step = 20;

void mode_accel_decel_spin(){
	if(isButtonPressed(1) == 1 && temp_accel_decel_spin == 0){
		// setup LCD
		reset_animation_pos();
		lcd_clear_display();
		display_while_playing();

		//init speed
		speed = 500;
		setTimer(TIMER_SPIN_ID, speed); // Timer để hiển thị LED (theo speed hiện tại)
		setTimer(TIMER_ACCEL_ID, 100);  // Timer cố định 100ms để tính toán tốc độ

		setButtonFlag(1);
		temp_accel_decel_spin++;
		check = 0;
	}

	if(temp_accel_decel_spin > 0){
		display_while_playing();
	}

	//speed up
	if(isButtonLongPressed(1) == 1){
		check = 0;
	}
	//slow down
	if(isButtonReleased(1) == 1){
		check = 1;
	}

	//display 7SEG base on speed
	if(isTimerExpired(TIMER_SPIN_ID) == 1 && temp_accel_decel_spin > 0) {
		update_led_buffer(random_digit(), random_digit(), random_digit());
		display_3_digit();
		setTimer(TIMER_SPIN_ID, speed);
	}

	//increase/decrease speed_step per 100ms
	if(isTimerExpired(TIMER_ACCEL_ID) == 1 && temp_accel_decel_spin > 0){
		setTimer(TIMER_ACCEL_ID, 100);

		if(check == 0){
			//speed up
			if(speed > 10){
				speed -= speed_step;
				if(speed < 10) speed = 10; //min
			}
		}
		else{
			//slow down
			if(speed < 500){
				speed += speed_step;
			}
			else{
				//test demo
                apply_test_result_single();

				//stop
				if(check_result_single_player()){
					display_announcement(BIGWIN);
					PlayJackpotTune();
					Led_BlinkGreen();
					display_list_button();
				}

				else{
					display_announcement(BETTER_LUCK_NEXT_TIME);
					PlaySadLoseTune();
					Led_BlinkRed();
					display_list_button();
				}

				// reset
				speed = 500;
				check = 0;
				temp_accel_decel_spin = 0;
			}
		}
	}
}

void display7SEG_mode_accel_decel_spin(){
	led_buffer[0] = 0;
	led_buffer[1] = 0;
	led_buffer[2] = 3;
	display_3_digit();
}

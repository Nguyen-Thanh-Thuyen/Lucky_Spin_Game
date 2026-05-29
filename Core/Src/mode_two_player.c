/*
 * mode_two_player.c
 *
 *  Created on: Apr 9, 2026
 *      Author: thuyen
 */


#include "mode_two_players.h"
#include "button.h"
#include "global.h"
#include "software_timer.h"
#include "display_7SEG.h"
#include "display_LCD.h"
#include "display_7SEG.h"
#include "random_gen.h"
#include "logic_game.h"
#include "led_anounce.h"

// include lcd

int first_player_buffer[5] = {0, 0, 0, 0, 0};
int second_player_buffer[5] = {0, 0, 0, 0, 0};
int index_player = 1;
int check_result_two_players(){
	//calculate point
	first_player_buffer[3] = first_player_buffer[0] + first_player_buffer[1] + first_player_buffer[2];
	second_player_buffer[3] = second_player_buffer[0] + second_player_buffer[1] + second_player_buffer[2];

	first_player_buffer[4] = SUM_MASTER;
	second_player_buffer[4] = SUM_MASTER;

	//DOUBLE EDGE
	if(first_player_buffer[0] == first_player_buffer[1]
		|| first_player_buffer[0] == first_player_buffer[2]
		|| first_player_buffer[1] == first_player_buffer[2]){
		first_player_buffer[4] = DOUBLE_EDGE;
	}
	if(second_player_buffer[0] == second_player_buffer[1]
		|| second_player_buffer[0] == second_player_buffer[2]
		|| second_player_buffer[1] == second_player_buffer[2]){
		second_player_buffer[4] = DOUBLE_EDGE;
	}

	//TRIPLE WIN
	if(first_player_buffer[0] == first_player_buffer[1]
		&& first_player_buffer[0] == first_player_buffer[2]){
		first_player_buffer[4] = TRIPLE_WIN;
	}
	if(second_player_buffer[0] == second_player_buffer[1]
		&& second_player_buffer[0] == second_player_buffer[2]){
		second_player_buffer[4] = TRIPLE_WIN;
	}

	//find winer
	if(first_player_buffer[4] > second_player_buffer[4]){
		return FIRST_PLAYER;
	}
	else if(first_player_buffer[4] < second_player_buffer[4]){
		return SECOND_PLAYER;
	}
	else if(first_player_buffer[4] == second_player_buffer[4]){
		if(first_player_buffer[3] > second_player_buffer[3]){
			return FIRST_PLAYER;
		}
		else if(first_player_buffer[3] < second_player_buffer[3]){
			return SECOND_PLAYER;
		}
		else if(first_player_buffer[3] == second_player_buffer[3]){
			return DRAW;
		}
	}
	return 0;
}
void mode_two_players(){
	//static variables track turn displaying
	static int current_displayed_index = 0;
	//flag waiting resulut
	static int waiting_result = 0;

	if(waiting_result == 1){
		//waiting result time out
		if (isTimerExpired(TIMER_WAIT_RESULT)) {
			waiting_result = 0;
			index_player = 1;
			current_displayed_index = 0;

			// Tăng index test sau khi đã hoàn thành cả 2 lượt chơi và xem kết quả
			#if TEST_MODE
			    test_idx_multi++;
			    if (test_idx_multi >= 3) test_idx_multi = 0; // 0->1->2->0
			#endif
		}
		else return;
	}

	if(spin_flag == 0 && waiting_result == 0){
		// display "Player X Turn"
		if(current_displayed_index != index_player){
			lcd_clear_display();
			display_mode_two_players(index_player);
			current_displayed_index = index_player;
		}
	}
	if(isButtonPressed(1) == 1 && waiting_result == 0) {
		spin_flag = 1;
		last_time = HAL_GetTick();

		//setup LCD
		reset_animation_pos();
		lcd_clear_display();
		display_while_playing();
		setTimer(SPIN, 10);
		setButtonFlag(1);
	}

	if(spin_flag == 1 && isTimerExpired(SPIN) == 1){
		if(HAL_GetTick() - last_time < 3000){
			update_led_buffer(random_digit(), random_digit(), random_digit());
			display_3_digit();
			display_while_playing();
			setTimer(SPIN, 100);
		}
		else{
			spin_flag = 0;
			//test demo
            #if TEST_MODE
                int p_idx = (index_player == 1) ? 0 : 1; // 0 là P1, 1 là P2
                led_buffer[0] = test_multi_data[test_idx_multi][p_idx][0];
                led_buffer[1] = test_multi_data[test_idx_multi][p_idx][1];
                led_buffer[2] = test_multi_data[test_idx_multi][p_idx][2];
                display_3_digit(); // Hiện số đã force
            #endif
            // --------------------------------------

			if(index_player == 1){
				first_player_buffer[0] = led_buffer[0];
				first_player_buffer[1] = led_buffer[1];
				first_player_buffer[2] = led_buffer[2];

				//turn to the second
				index_player = 2;
			}
			else if(index_player == 2){
				second_player_buffer[0] = led_buffer[0];
				second_player_buffer[1] = led_buffer[1];
				second_player_buffer[2] = led_buffer[2];

				//check result
				switch(check_result_two_players()){
				case FIRST_PLAYER:
					Led_BlinkRed();
					display_announcement(P2_LOSE);
					break;
				case SECOND_PLAYER:

					Led_BlinkGreen();
					display_announcement(P1_LOSE);
					break;
				case DRAW:
					Led_BlinkBoth();
					display_announcement(TIE);
					break;
				default:
					break;
				}

				waiting_result = 1;
				setTimer(TIMER_WAIT_RESULT, 2000); // 2000ms

			}
		}
	}
}

void display7SEG_mode_two_players(){
	led_buffer[0] = 0;
	led_buffer[1] = 0;
	led_buffer[2] = 4;
	display_3_digit();
}

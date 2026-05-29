/*
 * logic_game.c
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#include "global.h"
#include "logic_game.h"
#include "display_7SEG.h"
#include "button.h"
#include "random_gen.h"
#include "software_timer.h"

// TEST CASE
#if TEST_MODE
    int test_single_data[2][3] = {
        {6, 4, 9}, // loss
        {9, 9, 9}  // win
    };
    int test_idx_single = 0;

    //[Round][Player][Digit]
    int test_multi_data[3][2][3] = {
        {{5, 7, 5}, {2, 8, 3}}, // Case 0: P1 Win
        {{4, 6, 1}, {6, 9, 5}}, // Case 1: P2 Win
        {{7, 7, 7}, {7, 7, 7}}  // Case 2: Draw
    };
    int test_idx_multi = 0;
#endif

// --- APLLY TEST ---
void apply_test_result_single() {
    #if TEST_MODE
        led_buffer[0] = test_single_data[test_idx_single][0];
        led_buffer[1] = test_single_data[test_idx_single][1];
        led_buffer[2] = test_single_data[test_idx_single][2];

        display_3_digit();
        // 0 -> 1 -> 0
        test_idx_single++;
        if (test_idx_single >= 2) test_idx_single = 0;
    #endif
}

void logic_game(){
	switch (status){
	case INIT:
		update_led_buffer(9, 9, 9);
		display_3_digit();
		display_welcome_screen();
		if(isButtonPressed(3) == 1){
			lcd_clear_display();
			status = LIST_MODES;
			setButtonFlag(3);
		}
		break;
	case MODE_SINGLE_SPIN:
		//open list mode
		if(isButtonPressed(3) == 1)
		{
			lcd_clear_display();
			status = LIST_MODES;
			setButtonFlag(3);
			break;
		}
		//play
		mode_single_spin();

		break;
	case MODE_HOLD_SPIN:
		//open list mode
		if(isButtonPressed(3) == 1)
		{
			lcd_clear_display();
			status = LIST_MODES;
			setButtonFlag(3);
			break;
		}
		//play
		mode_hold_spin();
		break;
	case MODE_ACCEL_DECEL_SPIN:
		//open list mode
		if(isButtonPressed(3) == 1)
		{
			lcd_clear_display();
			status = LIST_MODES;
			setButtonFlag(3);
			break;
		}
		//play
		mode_accel_decel_spin();
		break;
	case MODE_TWO_PLAYERS:
		//open list mode
		if(isButtonPressed(3) == 1)
		{
			lcd_clear_display();
			status = LIST_MODES;
			setButtonFlag(3);
			break;
		}
		//play
		if(isTimerExpired(WAIT_SCREEN_2P)) mode_two_players();
		break;
	case HOME_SCREEN:
		//open list mode
		display_welcome_screen();
		if(isButtonPressed(3) == 1)
		{
			update_led_buffer(9, 9, 9);
			display_3_digit();
			lcd_clear_display();
			status = LIST_MODES;
			choose_mode = INIT;
			setButtonFlag(3);
			break;
		}
	case LIST_MODES:
		display_list_modes();
		break;
	}
}

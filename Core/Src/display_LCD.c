/*
 * display_LCD.c
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */


#include "display_LCD.h"


// Điều khiển vị trí hiện tại
int pos_left  = RUN_COL_END; // Hàng 1 chạy từ phải → trái
int pos_right = RUN_COL_START; // Hàng 2 chạy từ trái → phải

int currmark = 0;


void display_init() {
    lcd_init();
    setTimer(TIMER_LCD_ANIMATION, LCD_UPDATE_CYCLE);
    setTimer(TIMER_BLINK, BLINK_CYCLE);

}

/* ========== Welcome Screen ========== */
void display_welcome_screen() {
    lcd_goto_XY(0, 3);
    lcd_send_string("Lucky Spin Game");

    display_list_button();
}

/* ========== Announcement ========== */
void display_announcement(int announce_num) {
	lcd_clear_display();
    switch (announce_num){
    case START:
    	lcd_goto_XY(0, 8);
    	lcd_send_string("START");
    	break;
    case BIGWIN:
    	lcd_goto_XY(0, 6);
    	lcd_send_string("BIG WIN!");
    	break;
    case BETTER_LUCK_NEXT_TIME:
    	lcd_goto_XY(0, 0);
    	lcd_send_string("GOOD LUCK NEXT TIME!");
    	break;
    case P1_LOSE:
    	lcd_goto_XY(1, 5);
    	lcd_send_string("P1");
    	lcd_goto_XY(1, 13);
    	lcd_send_string("P2");
    	lcd_goto_XY(2, 3);
    	lcd_send_string("LOSER");
    	lcd_goto_XY(2, 12);
    	lcd_send_string("WINER");
    	break;
    case P2_LOSE:
    	lcd_goto_XY(1, 5);
    	lcd_send_string("P1");
    	lcd_goto_XY(1, 13);
    	lcd_send_string("P2");
    	lcd_goto_XY(2, 3);
    	lcd_send_string("WINER");
    	lcd_goto_XY(2, 12);
    	lcd_send_string("LOSER");
    	break;
    case TIE:
    	lcd_goto_XY(1, 5);
    	lcd_send_string("P1");
    	lcd_goto_XY(1, 13);
    	lcd_send_string("P2");
    	lcd_goto_XY(2, 1);
    	lcd_send_string("THE SCORE IS EVEN!");
    	break;
    default:
    	break;
    }
}



/* ========== Hàm hiển thị màn hình khi trò chơi đang chạy ========== */
void display_while_playing() {
	if (!isTimerExpired(TIMER_LCD_ANIMATION)) {
	    return;
	}

	    // --- Reset Timer cho lần sau ---
	setTimer(TIMER_LCD_ANIMATION, LCD_UPDATE_CYCLE);
    char line1[21];
    char line2[21];

    // clear buffer
    for (int i = 0; i < 20; i++) {
        line1[i] = ' ';
        line2[i] = ' ';
    }
    line1[20] = '\0';
    line2[20] = '\0';

    // --- VẼ MŨI TÊN TRÊN HÀNG 1 (<<<) ---
    for (int i = 0; i < ARROW_LEN; i++) {
        int col = pos_left - i;
        if (col >= RUN_COL_START && col <= RUN_COL_END)
            line1[col] = '<';
    }

    // --- VẼ MŨI TÊN TRÊN HÀNG 2 (>>>) ---
    for (int i = 0; i < ARROW_LEN; i++) {
        int col = pos_right + i;
        if (col >= RUN_COL_START && col <= RUN_COL_END)
            line2[col] = '>';
    }

    // In ra LCD
    lcd_goto_XY(1, 0);
    lcd_send_string(line1);

    lcd_goto_XY(2, 0);
    lcd_send_string(line2);

    // --- CẬP NHẬT VỊ TRÍ ---
    pos_left--;          // <<< di chuyển trái
    pos_right++;         // >>> di chuyển phải

    // Reset vòng lặp
    if (pos_left < (RUN_COL_START - ARROW_LEN))
        pos_left = RUN_COL_END;

    if (pos_right > (RUN_COL_END + 1))
        pos_right = RUN_COL_START - ARROW_LEN + 1;
}

void reset_animation_pos(){
    pos_left  = RUN_COL_END;
    pos_right = RUN_COL_START;
}

void display_list_modes(){
	switch(choose_mode){
	case INIT:
		choose_mode = LIST_MODES;
		break;
	case LIST_MODES:
		lcd_goto_XY(0, 0);
		lcd_send_string("  Single Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("  Hold Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("  Acc Decel Spin");

		lcd_goto_XY(3, 0);
		lcd_send_string("  Two Players");
		if(isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = MODE_SINGLE_SPIN;
			setButtonFlag(0);
		}
		break;


	case MODE_SINGLE_SPIN:
		lcd_goto_XY(0, 0);
		lcd_send_string("> Single Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("  Hold Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("  Acc Decel Spin");

		lcd_goto_XY(3, 0);
		lcd_send_string("  Two Players");

		if(isButtonPressed(2) == 1){
			status = MODE_SINGLE_SPIN;

			display7SEG_mode_single_spin();

			lcd_clear_display();
			lcd_goto_XY(1, 5);
			lcd_send_string("Single Spin");

			lcd_goto_XY(3, 2);
			lcd_send_string("Press B1 to spin");

			setButtonFlag(2);
			break;
		}
		if(isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = MODE_HOLD_SPIN;
			setButtonFlag(0);
		}

		break;
	case MODE_HOLD_SPIN:
		lcd_goto_XY(0, 0);
		lcd_send_string("  Single Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("> Hold Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("  Acc Decel Spin");

		lcd_goto_XY(3, 0);
		lcd_send_string("  Two Players");

		if(isButtonPressed(2) == 1){
			status = MODE_HOLD_SPIN;

			display7SEG_mode_hold_spin();

			lcd_clear_display();
			lcd_goto_XY(1, 5);
			lcd_send_string("Hold Spin");
			lcd_goto_XY(3, 2);
			lcd_send_string("Press B1 to spin");

			setButtonFlag(2);
			break;
		}
		if(isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = MODE_ACCEL_DECEL_SPIN;
			setButtonFlag(0);
		}

		break;
	case MODE_ACCEL_DECEL_SPIN:
		lcd_goto_XY(0, 0);
		lcd_send_string("  Single Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("  Hold Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("> Acc Decel Spin");

		lcd_goto_XY(3, 0);
		lcd_send_string("  Two Players");

		if(isButtonPressed(2) == 1){
			status = MODE_ACCEL_DECEL_SPIN;

			display7SEG_mode_accel_decel_spin();

			lcd_clear_display();
			lcd_goto_XY(1, 3);
			lcd_send_string("Acc Decel Spin");
			lcd_goto_XY(3, 2);
			lcd_send_string("Press B1 to spin");

			setButtonFlag(2);
			break;
		}

		if (isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = MODE_TWO_PLAYERS;
			setButtonFlag(0);
		}
		break;
	case MODE_TWO_PLAYERS:
		lcd_goto_XY(0, 0);
		lcd_send_string("  Single Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("  Hold Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("  Acc Decel Spin");

		lcd_goto_XY(3, 0);
		lcd_send_string("> Two Players");

		if(isButtonPressed(2) == 1){
			status = MODE_TWO_PLAYERS;

			display7SEG_mode_two_players();

			lcd_clear_display();
			lcd_goto_XY(1, 5);
			lcd_send_string("Two Players");

			setTimer(WAIT_SCREEN_2P, 1000);
			setButtonFlag(2);
			break;
		}

		if(isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = WELCOME_SCREEN;
			setButtonFlag(0);
		}
		break;
	case WELCOME_SCREEN:
		lcd_goto_XY(0, 0);
		lcd_send_string("  Hold Spin");

		lcd_goto_XY(1, 0);
		lcd_send_string("  Acc Decel Spin");

		lcd_goto_XY(2, 0);
		lcd_send_string("  Two Players");

		lcd_goto_XY(3, 0);
		lcd_send_string("> Home screen");


		if(isButtonPressed(2) == 1){
			update_led_buffer(9, 9, 9);
			display_3_digit();
			lcd_clear_display();
			status = HOME_SCREEN;
			choose_mode = HOME_SCREEN;
			break;
		}

		if(isButtonPressed(0) == 1){
			lcd_clear_display();
			choose_mode = MODE_SINGLE_SPIN;
			setButtonFlag(0);
		}
		break;
	case HOME_SCREEN:
		if(isButtonPressed(3) == 1)
		{
			lcd_clear_display();
			//status = INIT ;
			setButtonFlag(3);
			break;
		}
		break;
	default:
		break;
	}
};

void display_mode_two_players(int index_player){
	if(index_player == 1){
		lcd_goto_XY(1, 0);
		lcd_send_string("First Player");
		lcd_goto_XY(3, 2);
		lcd_send_string("Press B1 to spin");
	}else if (index_player == 2){
		lcd_goto_XY(1, 7);
		lcd_send_string("Second Player");
		lcd_goto_XY(3, 2);
		lcd_send_string("Press B1 to spin");
	}
}
void display_list_button(){
	lcd_goto_XY(2, 1);
	lcd_send_string("B0");
	lcd_goto_XY(2, 6);
	lcd_send_string("B1");
	lcd_goto_XY(2, 12);
	lcd_send_string("B2");
	lcd_goto_XY(2, 17);
	lcd_send_string("B3");

	lcd_goto_XY(3, 0);
	lcd_send_string("MODE");
	lcd_goto_XY(3, 5);
	lcd_send_string("SPIN");
	lcd_goto_XY(3, 11);
	lcd_send_string("ACPT");
	lcd_goto_XY(3, 16);
	lcd_send_string("LIST");
}

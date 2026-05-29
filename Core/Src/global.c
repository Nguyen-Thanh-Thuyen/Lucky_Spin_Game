/*
 * global.c
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#include "global.h"

int choose_mode = INIT;
int status = INIT;
int last_time = 0;
int spin_flag = 0;



int led_buffer[MAX_LED] = {1, 2, 3};
int check_result_single_player(){
	if (led_buffer[0] == led_buffer[1] && led_buffer[1] == led_buffer[2]){
		return 1;
	}
	return 0;
}

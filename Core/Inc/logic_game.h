/*
 * logic_game.h
 *
 *  Created on: Apr 20, 2026
 *      Author: thuyen
 */

#ifndef INC_LOGIC_GAME_H_
#define INC_LOGIC_GAME_H_

#include "global.h"


#define TEST_MODE 1 // 1: TEST, 0 NORMAL

//declare test variable
#if TEST_MODE
    extern int test_idx_single;
    extern int test_single_data[2][3];
    extern int test_idx_multi;
    extern int test_multi_data[3][2][3];

    void apply_test_result_single(void);
#endif


void FSM_game_control();
void logic_game();

#endif /* INC_LOGIC_GAME_H_ */

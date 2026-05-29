/*
 * mode_two_players.h
 *
 *  Created on: Apr 9, 2026
 *      Author: thuyen
 */

#ifndef INC_MODE_TWO_PLAYERS_H_
#define INC_MODE_TWO_PLAYERS_H_


#define TRIPLE_WIN 		3
#define DOUBLE_EDGE		2
#define SUM_MASTER		1

#define FIRST_PLAYER	1
#define SECOND_PLAYER	2

#define DRAW			99

extern int first_player_buffer[5];
extern int second_player_buffer[5];

int check_result_two_players();
void mode_two_players();
void display7SEG_mode_two_players();


#endif /* INC_MODE_TWO_PLAYERS_H_ */

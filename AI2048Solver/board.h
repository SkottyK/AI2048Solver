//
//  board.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef board_h
#define board_h

#include <stdio.h>
#include "2048.h"

struct board_data;
typedef struct board_data *Board;

Board empty_board();
Board board_from_arr(int exp[4][4]);
void free_board(Board b);

void place_rand(Board b);
void place(Board b, int r, int c, int val);
int bget(Board b, int row, int col);

PointList open_spaces(Board b);
Move *valid_moves(Board b, int *size);
void shift(Board b, Move m);

void print_board(Board b);

/* Exposed for testing only */
Board rotate_for_move(Board og, Move m);
Board invert_rotate_for_move(Board og, Move m);
int explicit_equal(Board b, int exp[4][4]);

#endif /* board_h */

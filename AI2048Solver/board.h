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
#include "move.h"
#include "point.h"

#define BOARDSIZE 4

struct board_data;
typedef struct board_data *Board;

Board empty_board();
Board board_from_arr(int exp[BOARDSIZE][BOARDSIZE]);
Board board_cpy(Board b);
void free_board(Board b);

void place_rand(Board b);
void place(Board b, int r, int c, int val);
int bget(Board b, int row, int col);

PointList open_spaces(Board b);
Move *effectual_moves(Board b, int *size);
int is_effectual_move(Board b, Move m);
int is2048(Board b);
int max_tile(Board b);
int shift(Board b, Move m);

void print_board(Board b);

/* Exposed for testing only */
Board rotate_for_move(Board og, Move m);
Board invert_rotate_for_move(Board og, Move m);
int explicit_equal(Board b, int exp[BOARDSIZE][BOARDSIZE]);

#endif /* board_h */

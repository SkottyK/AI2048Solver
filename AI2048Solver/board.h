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

Board shift(Board b, Move m);
Board place_rand(Board b);
Board place(Board b, int r, int c, int val);

Point *open_spaces(Board b);
Move *valid_moves(Board b);

int get(Board b, int row, int col);
void set(Board b, int row, int col, int val);
void print_board(Board b);

#endif /* board_h */

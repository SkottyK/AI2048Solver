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

struct board_data;
typedef struct board_data *board;

board empty_board();
int get(board B, int row, int col);
void set(board B, int row, int col, int val);
void print_board(board B);

#endif /* board_h */

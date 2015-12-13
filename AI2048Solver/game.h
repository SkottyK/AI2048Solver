//
//  game.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/1/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef game_h
#define game_h

#include "board.h"
#include "heuristics.h"
#include "move.h"

typedef struct game_data {
    Heuristic h;
    Board board;
    int score;
} *Game;

Game init_game(Heuristic h);
Game game_cpy(Game og);
void game_free(Game g);

void make_move(Game g, Move m);
Game test_move(Game g, Move m);
void print_game(Game g);
double expected_value(Game g, Move m, int n);

#endif /* game_h */

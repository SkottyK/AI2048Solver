//
//  game.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/1/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef game_h
#define game_h

#include "2048.h"
#include "board.h"

typedef int (*Heuristic)(Board B);

typedef struct game_data {
    Heuristic h;
    Board board;
    int score;
} *Game;

Game init_game(Heuristic h);

void make_move(Game g, Move m);
int test_move(Game g, Move m);

/* Play game on command line */
void human_game();

#endif /* game_h */

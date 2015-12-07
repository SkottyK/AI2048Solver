//
//  game.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/1/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

#define MAXLINE 400

Game init_game(Heuristic h) {
    srand((unsigned)time(NULL));
    Game g = (Game)malloc(sizeof(struct game_data));

    g->board = empty_board();
    place_rand(g->board);
    place_rand(g->board);
    g->h = h;
    g->score = 0;

    return g;
}
Game game_cpy(Game og) {
    Game g = (Game)malloc(sizeof(struct game_data));
    g->board = board_cpy(og->board);
    g->h = og->h;
    g->score = 0;
    return g;
}

void print_game(Game g) {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Score: %d\n", g->score);
    print_board(g->board);
    printf("Heuristic:\n");
    printf("     Up: %d\n", estimate_move(g, Up));
    printf("   Down: %d\n", estimate_move(g, Down));
    printf("   Left: %d\n", estimate_move(g, Left));
    printf("  Right: %d\n", estimate_move(g, Right));
}

void make_move(Game g, Move m) {
    if (is_effectual_move(g->board, m)) {
        g->score += shift(g->board, m);
        place_rand(g->board);
    }
}

Game test_move(Game og, Move m) {
    if (is_effectual_move(og->board, m)) {
        Game g = game_cpy(og);
        make_move(g, m);
        return g;
    }
    return NULL;
}

int estimate_move(Game g, Move m) {
    if (is_effectual_move(g->board, m)) {
        Board b = board_cpy(g->board);
        shift(b, m);
        int hval = g->h(b);
        free(b);
        return hval;
    }
    return -1;
}




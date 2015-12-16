//
//  game.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/1/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define MAXLINE 400

Game init_game(Heuristic h) {
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
void game_free(Game g) {
    free_board(g->board);
    free(g);
}


void estimate_str(Game g, Move m, char res[10]) {
    double result = expected_value(g, m, 1);
    if (result == -HUGE_VAL) {
        sprintf(res, "INVALID");
    } else {
        sprintf(res, "%f", result);
    }
}

void print_game(Game g) {
    char fbuf[10];
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Score: %d\n", g->score);
    print_board(g->board);
    printf("Heuristic:\n");
    estimate_str(g, Up, fbuf);
    printf("     Up: %s\n", fbuf);
    estimate_str(g, Down, fbuf);
    printf("   Down: %s\n", fbuf);
    estimate_str(g, Left, fbuf);
    printf("   Left: %s\n", fbuf);
    estimate_str(g, Right, fbuf);
    printf("  Right: %s\n", fbuf);
}

void make_move(Game g, Move m) {
    if (is_effectual_move(g->board, m)) {
        g->score += shift(g->board, m);
        place_rand(g->board);
    }
}

Game test_move_norand(Game og, Move m) {
    if (is_effectual_move(og->board, m)) {
        Game g = game_cpy(og);
        g->score += shift(g->board, m);
        return g;
    }
    return NULL;
}

Game test_move(Game og, Move m) {
    if (is_effectual_move(og->board, m)) {
        Game g = game_cpy(og);
        make_move(g, m);
        return g;
    }
    return NULL;
}


/* Returns -HUGEVAL if there is nothing to do */
double expected_value(Game g, Move m, int n) {
    if (n < 1) {
        if (is_effectual_move(g->board, m)) {
            Board b = board_cpy(g->board);
            shift(b, m);
            place_rand(b);
            double hval = g->h(b);
            free(b);
            return hval;
        }
        return -HUGE_VAL;
    } else {
        double sum = 0.0;
        int neffectual;
        for (Move m=Up; m <= Right; m++) {
            double result = expected_value(g, m, n - 1);
            if (result != -HUGE_VAL) {
                neffectual++;
                sum += result;
            }
        }
        if (neffectual)
            return sum / (double)neffectual;
        return -HUGE_VAL;
    }
}





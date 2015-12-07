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
#include "heuristics.h"
#include "game.h"

#define MAXLINE 400

Game init_game(Heuristic h) {
    srand((unsigned)time(NULL));
    Game g = (Game)malloc(sizeof(struct game_data));

    Board b = empty_board();
    place_rand(b);
    place_rand(b);
    g->board = b;
    g->h = h;
    g->score = 0;

    return g;
}

void print_game(Game g) {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Score: %d\n", g->score);
    print_board(g->board);
    printf("Heuristic:\n");
    printf("     Up: %d\n", test_move(g, Up));
    printf("   Down: %d\n", test_move(g, Down));
    printf("   Left: %d\n", test_move(g, Left));
    printf("  Right: %d\n", test_move(g, Right));
}

void make_move(Game g, Move m) {
    if (is_effectual_move(g->board, m)) {
        g->score += shift(g->board, m);
        place_rand(g->board);
    }
}

int test_move(Game g, Move m) {
    if (is_effectual_move(g->board, m)) {
        Board b = board_cpy(g->board);
        shift(b, m);
        int hval = g->h(b);
        free(b);
        return hval;
    }
    return -1;
}

void print_commands() {
    printf("Controls:\n");
    printf("       Up: u\n");
    printf("     Down: d\n");
    printf("     Left: l\n");
    printf("    Right: r\n");
    printf("     Quit: q\n");
    printf("     Help: h\n");
    printf("\n\nGood Luck!\n\n");
}

void human_game() {
    printf("Welcome to 2048!\n");
    print_commands();


    //char buf[MAXLINE];
    Game g = init_game(sum_heuristic);
    print_game(g);

    char in;
    int playing = 1;
    while (playing) {
        in = getc(stdin);
        if (in == '\033') {
            getc(stdin);
            switch (getc(stdin)) {
                case 'A':
                    in = 'u';
                    break;
                case 'B':
                    in = 'd';
                    break;
                case 'C':
                    in = 'r';
                    break;
                case 'D':
                    in = 'l';
                    break;
                default:
                    break;
            }
        }
        switch (in) {
            case 'q':
                playing = 0;
                break;
            case 'u':
                make_move(g, Up);
                print_game(g);
                break;
            case 'd':
                make_move(g, Down);
                print_game(g);
                break;
            case 'l':
                make_move(g, Left);
                print_game(g);
                break;
            case 'r':
                make_move(g, Right);
                print_game(g);
                break;
            case 'h':
                print_commands();
                break;
            default:
                break;
        }
        if (pl_empty(open_spaces(g->board))) {
            playing = 0;
        }
    }
    print_game(g);
    printf("Game Over! Final Score: %d\n", g->score);
}



//
//  game.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/1/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "game.h"

#define MAXLINE 400

Game init_game(Heuristic h) {
    Game g = (Game)malloc(sizeof(struct game_data));

    Board b = empty_board();
    place_rand(b);
    place_rand(b);
    g->board = b;
    g->h = h;
    g->score = 0;

    return g;
}

void make_move(Game g, Move m) {
    g->score += shift(g->board, m);
    place_rand(g->board);
}

void print_commands() {
    printf("Controls:\n");
    printf("       Up: u\n");
    printf("     Down: d\n");
    printf("     Left: l\n");
    printf("    Right: r\n");
    printf("     Quit: q\n");
    printf("\n\nGood Luck!\n\n");
}

void human_game() {
    printf("Welcome to 2048!\n");
    print_commands();


    char buf[MAXLINE];
    Game g = init_game(NULL);

    int playing = 1;
    while (playing) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Score: %d\n", g->score);
        print_board(g->board);

        fgets(buf, MAXLINE, stdin);
        if (strlen(buf) > 0) {
            switch (buf[0]) {
                    case 'q':
                    playing = 0;
                    break;
                    case 'u':
                    make_move(g, Up);
                    break;
                    case 'd':
                    make_move(g, Down);
                    break;
                    case 'l':
                    make_move(g, Left);
                    break;
                    case 'r':
                    make_move(g, Right);
                    break;
                default:
                    printf("Command not recognized.\n");
                    print_commands();
                    break;

            }
            if (pl_empty(open_spaces(g->board))) {
                playing = 0;
            }
        }
    }
    printf("Game Over! Final Score: %d\n", g->score);
}



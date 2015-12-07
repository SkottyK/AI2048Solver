//
//  2048.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/24/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include "2048.h"
#include "board.h"
#include "game.h"
#include "heuristics.h"
#include "move.h"
#include "num_util.h"


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
    Game g = init_game(squaresum_heuristic);
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

void baseline(int num_tests) {
    int scores[num_tests];

    for (int i=0; i < num_tests; i++) {
        Game g = init_game(squaresum_heuristic);
        while (!pl_empty(open_spaces(g->board))) {
            make_move(g, (Move)randint(4));
        }
        scores[i] = g->score;
    }

    for (int i = 0; i < num_tests; i++) {
        printf("%d\n", scores[i]);
    }
    printf("\n\n");
}



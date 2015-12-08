//
//  2048.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/24/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//
#include <stdlib.h>
#include "list.h"
#include "2048.h"
#include "board.h"
#include "point.h"
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


int play2048(Game g) {
    int* size = (int*)malloc(sizeof(int));
    while(!is2048(g->board)) {
        //print_board(g->board);
        Move* moves = effectual_moves(g->board, size);
        //printf("num_moves %d\n", *size);
        if (moves == NULL || *size == 0) {
            //printf("No more moves, game over!\n");
            return g->score;
            break;
        }
        int i;
        Move bestMove = moves[0];
        int bestHeur = 0;
        for (i = 0; i < *size; i++) {
            Game test = test_move(g, moves[i]);
            PointList pl = open_spaces(test->board);
            if (pl->N == 0) //This should never happen
                continue;
            listNode *node = pl->points.head;
            int maxheur = 0;
            while (node != NULL) {
                Board cpy = board_cpy(test->board);
                Board cpy2 = board_cpy(test->board);
                Point p = (Point)node->data;
                place(cpy,p->r, p->c, 2);
                int twoheur = (*(test->h))(cpy);
                place(cpy2, p->r, p->c, 4);
                int fourheur = (*(test->h))(cpy2);
                int heur = twoheur > fourheur ? twoheur : fourheur;
                maxheur = maxheur > heur ? maxheur : heur;
                node = node->next;
            }
            if (maxheur > bestHeur) {
                bestHeur = maxheur;
                bestMove = moves[i];
            }
        }
        make_move(g, bestMove);
        
    }
    free(size);
    return g->score;
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
    int scores[4][num_tests];

    for (int i=0; i < num_tests; i++) {
        Game g = init_game(squaresum_heuristic);
        Game g2 = init_game(squaresum_heuristic);
        Game g3 = init_game(weighted_sum1);
        Game g4 = init_game(empty_blocks);
        while (!pl_empty(open_spaces(g->board))) {
            make_move(g, (Move)randint(4));
        }
        scores[0][i] = g->score;
        scores[1][i] = play2048(g2);
        scores[2][i] = play2048(g3);
        scores[3][i] = play2048(g4);
    }

    printf("Baseline,Square Sum,Weight Sequence,Empty Blocks\n");
    for (int i = 0; i < num_tests; i++) {
        printf("%d,%d,%d,%d\n", scores[0][i], scores[1][i], scores[2][i], scores[3][i]);
    }
    printf("\n");
}



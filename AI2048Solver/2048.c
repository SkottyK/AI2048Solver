//
//  2048.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/24/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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

#define NUM_PLY 1
//Applies NUM_PLY number of plys
Move ply(Game g) {
    Board b = g->board;
    int* size = (int*)malloc(sizeof(int));
    Move* moves = effectual_moves(b, size);
    if (moves == NULL || *size == 0)
        return g->score;
    int i;
    
    free(size);
    return moves[0];
}

int play2048(Game g) {
    int size;
    while(!is2048(g->board)) {
        Move* moves = effectual_moves(g->board, size);
        if (moves == NULL || *size == 0)
            return g->score;
        int i;
        Move bestMove = moves[0];
        double bestHeur = 0;
        for (i = 0; i < size; i++) {
            Game test = test_move(g, moves[i]);
            PointList pl = open_spaces(test->board);
            if (pl->N == 0) {//This should never happen
                game_free(test);
                pl_free(pl);
                continue;
            }
            listNode *node = pl->points.head;
            double maxheur = 0;
            while (node != NULL) {
                Board cpy = board_cpy(test->board);
                Board cpy2 = board_cpy(test->board);
                Point p = (Point)node->data;
                place(cpy,p->r, p->c, 2);
                double twoheur = (*(test->h))(cpy);
                place(cpy2, p->r, p->c, 4);
                double fourheur = (*(test->h))(cpy2);
                double heur = twoheur > fourheur ? twoheur : fourheur;
                maxheur = maxheur > heur ? maxheur : heur;
                node = node->next;
                free_board(cpy);
                free_board(cpy2);
            }
            if (maxheur > bestHeur) {
                bestHeur = maxheur;
                bestMove = moves[i];
            }
            game_free(test);
            pl_free(pl);
        }
        make_move(g, bestMove);
        free(moves);
    }
    return g->score;
}


int playExpected2048(Game g, int depth) {
    int size;
    while(!is2048(g->board)) {
        Move* moves = effectual_moves(g->board, &size);
        // Test end conditions
        if (moves == NULL)
            break;
        if (size == 0) {
            free(moves);
            break;
        }
        int i;
        Move bestMove = moves[0];
        double bestE = 0;
        for (i = 0; i < size; i++) {
            double E = expected_value(g, moves[i], depth);
            if (E > bestE) {
                bestMove = moves[i];
                bestE = E;
            }
        }
        make_move(g, bestMove);
        free(moves);
    }
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
        PointList pl = open_spaces(g->board);
        if (pl_empty(pl)) {
            playing = 0;
        }
        pl_free(pl);
    }
    print_game(g);
    printf("Game Over! Final Score: %d\n", g->score);
}

void test_random(int *score, int *maxtile) {
    Game g = init_game(squaresum_heuristic);
    PointList pl = open_spaces(g->board);
    while (!pl_empty(pl)) {
        make_move(g, (Move)randint(4));
    }
    pl_free(pl);
    *score = g->score;
    *maxtile = max_tile(g->board);
    game_free(g);
}

void test_minimax(Heuristic h, int *score, int *maxtile) {
    Game g = init_game(h);
    *score = play2048(g);
    //*maxtile = max_tile(g->board);
    game_free(g);
}
void test_expectation(Heuristic h, int depth, int *score, int *maxtile) {
    Game g= init_game(h);
    *score = playExpected2048(g, depth);
    //*maxtile = max_tile(g->board);
    game_free(g);
}

void test_suite(int argc, const char *argv[]) {
    long num_tests = 100;
    FILE *score_file = stdout;
    FILE *tile_file = stdout;
    if (argc > 1) {
        // First argument should be number of trials
        num_tests = strtol(argv[1], NULL, 10);
        if (argc > 2) {
            const char *score_filename = argv[2];
            if ((score_file = fopen(score_filename, "w")) == NULL) {
                printf("Error: Could not open score file\n");
                exit(1);
            }
            if (argc > 3) {
                const char *score_filename = argv[3];
                if ((tile_file = fopen(score_filename, "w")) == NULL) {
                    printf("Error: Could not open max tile file\n");
                    exit(1);
                }
            }
        }
    }
    const char *f_labels = "Squaresum,Empty Blocks,Sequential Weight,Weight RC";
    Heuristic h_functions[] = {
        squaresum_heuristic,
        empty_blocks,
        weighted_sum1,
        weighted_sum2
    };
    int num_funcs = 4;
    int scores[num_funcs+1][num_tests];
    int mtiles[num_funcs+1][num_tests];

    for (int i=0; i < num_tests; i++) {
        test_random(&scores[0][i], &mtiles[0][i]);
        for (int h=0; h<num_funcs; h++) {
            test_minimax(h_functions[h], &scores[1+h][i], &mtiles[1+h][i]);
        }
    }

    fprintf(score_file, "Baseline,%s\n", f_labels);
    for (int i=0; i < num_tests; i++) {
        for (int j=0; j < num_funcs + 1; j++) {
            fprintf(score_file, "%d%s", scores[j][i], (j==num_funcs)?"\n":",");
        }
    }
    printf("\n");

    fprintf(tile_file, "Baseline,%s\n", f_labels);
    for (int i=0; i < num_tests; i++) {
        for (int j=0; j < num_funcs + 1; j++) {
            fprintf(tile_file, "%d%s", mtiles[j][i], (j==num_funcs)?"\n":",");
        }
    }
    printf("\n");
}



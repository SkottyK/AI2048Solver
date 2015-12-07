//
//  main.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "2048.h"
#include "board.h"
#include "point.h"
#include "game.h"



int test_rotate() {
    printf("Testing Rotate (visual check)\n");
    Board b = empty_board();

    for (int r=0; r<4; r++) {
        for (int c=0; c<4; c++) {
            place(b, r, c, (r+1) * 10 + (c+1));
        }
    }
    assert(pl_empty(open_spaces(b)));

    Board tmp, tmp2;
    printf("Original:\n");
    print_board(b);


    printf("\nRotate for up:\n");
    tmp = rotate_for_move(b, Up);
    tmp2 = invert_rotate_for_move(tmp, Up);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);


    printf("\nRotate for down:\n");
    tmp = rotate_for_move(b, Down);
    tmp2 = invert_rotate_for_move(tmp, Down);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);


    printf("\nRotate for left:\n");
    tmp = rotate_for_move(b, Left);
    tmp2 = invert_rotate_for_move(tmp, Left);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);
    
    return 0;
}

void fill(int test[4][4], int r0[4], int r1[4], int r2[4], int r3[4]) {
    for (int c = 0; c<4; c++) {
        test[0][c] = r0[c];
        test[1][c] = r1[c];
        test[2][c] = r2[c];
        test[3][c] = r3[c];
    }
}

int test_shift() {
    printf("Testing shift function\n");

    Board b;

    printf("    Testing on empty board...\n");
    b = empty_board();
    int zeroes[BOARDSIZE][BOARDSIZE];
    for (int r=0; r<BOARDSIZE; r++)
        for (int c=0; c<BOARDSIZE; c++)
            zeroes[r][c] = 0;
    assert(explicit_equal(b, zeroes));
    shift(b, Up);
    assert(explicit_equal(b, zeroes));
    shift(b, Down);
    assert(explicit_equal(b, zeroes));
    shift(b, Left);
    assert(explicit_equal(b, zeroes));
    shift(b, Right);
    assert(explicit_equal(b, zeroes));


    printf("    Extensive tests on right shift...\n");
    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 2, 2, 2, 2},
        { 2, 2, 2, 2},
        { 2, 2, 2, 2},
        { 2, 2, 2, 2}
    });
    shift(b, Right);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 0, 0, 4, 4},
        { 0, 0, 4, 4},
        { 0, 0, 4, 4},
        { 0, 0, 4, 4}
    }));
    free(b);

    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 8, 4, 8, 8},
        { 2, 8,32,64},
        { 2, 0, 0, 0},
        { 0, 0, 0, 2}
    });
    shift(b, Right);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 0, 8, 4,16},
        { 2, 8,32,64},
        { 0, 0, 0, 2},
        { 0, 0, 0, 2}
    }));
    free(b);

    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 0, 0, 4, 4},
        { 0, 2, 0, 2},
        { 0, 4, 0, 2},
        { 4, 0, 4, 0}
    });
    shift(b, Right);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 0, 0, 0, 8},
        { 0, 0, 0, 4},
        { 0, 0, 4, 2},
        { 0, 0, 0, 8}
    }));
    free(b);


    printf("    Tests on other directions...\n");
    printf("        Testing Up...\n");
    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 2, 2, 2, 2},
        { 2, 2, 2, 2},
        { 2, 2, 2, 2},
        { 2, 2, 2, 2}
    });
    shift(b, Up);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 4, 4, 4, 4},
        { 4, 4, 4, 4},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0}
    }));
    free(b);

    printf("        Testing Down...\n");
    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 8, 4, 8, 8},
        { 2, 8,32,64},
        { 2, 0, 0, 0},
        { 0, 0, 0, 2}
    });
    shift(b, Down);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 0, 0, 0, 0},
        { 0, 0, 0, 8},
        { 8, 4, 8,64},
        { 4, 8,32, 2}
    }));
    free(b);

    printf("        Testing Left...\n");
    b = board_from_arr((int[BOARDSIZE][BOARDSIZE]){
        { 8, 4, 8, 8},
        { 2, 8,32,32},
        { 2, 0, 0, 0},
        { 0, 0, 0, 2}
    });
    shift(b, Left);
    assert(explicit_equal(b, (int[BOARDSIZE][BOARDSIZE]){
        { 8, 4,16, 0},
        { 2, 8,64, 0},
        { 2, 0, 0, 0},
        { 2, 0, 0, 0}
    }));
    free(b);

    return 0;
}

int test_copy() {
    printf("Testing copy...\n");
    Board og = board_from_arr((int[4][4]){
        {2,3,4,5},
        {1,2,45,6},
        {10,-8,4,16},
        {34,6,8,25}
    });
    Board b1 = board_cpy(og);
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            if (bget(og,r,c) != bget(b1,r,c))
                printf("(%d,%d)\n", r,c);
            assert(bget(og,r,c) == bget(b1,r,c));
        }
    }
    free(og);
    free(b1);
    return 0;
}


int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
/*
    test_rotate();

    test_shift();

    test_copy();
    */
    human_game();

    return 0;
}

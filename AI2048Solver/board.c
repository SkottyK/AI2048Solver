//
//  board.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include "board.h"
#include "num_util.h"

#define N 4
#define NUMCHARS 5

struct board_data {
    int data[N][N];
};


/**********************************************************
 *   Initialization
 **********************************************************/
board empty_board() {
    board B = (board)calloc(1, sizeof(struct board_data));
    if (B == NULL) {
        fprintf(stderr, "Malloc failed to allocate board\n");
        exit(1);
    }
    return B;
}

/**********************************************************
 *   Accessors + Mutators
 **********************************************************/
int get(board B, int row, int col) {
    return B->data[row][col];
}
void set(board B, int row, int col, int val) {
    B->data[row][col] = val;
}



/**********************************************************
*   Printing
**********************************************************/
void print_horizontal() {
    for (int i=0; i < (N*NUMCHARS)+2; i++) {
        printf("-");
    }
    printf("\n");
}
void print_board(board B) {
    print_horizontal();
    for (int r=0; r < N; r++) {
        printf("|");
        for (int c=0; c < N; c++) {
            int val = get(B, r,c);
            for (int i=0; i < NUMCHARS - num_digits(val); i++)
                printf(" "); // Right-justify numbers
            printf("%d", val);
        }
        printf("|\n");
    }
    print_horizontal();
}



/*
  board.c
  AI2048Solver

  Created by Scott Krulcik on 11/21/15.
  Copyright © 2015 Scott Krulcik. All rights reserved.
 
 Idea behind rotating boards:
   Rotate board so desired move would always be to the right, then rotate back
   once done. This means the complex code only needs to be written once.

 */


#include <stdlib.h>
#include "board.h"
#include "num_util.h"

#define BOARDSIZE 4
#define NUMCHARS 5

struct board_data {
    int *data;
};
Move all_moves[4] = {Up, Down, Left, Right};

/**********************************************************
 *   Private Function Headers
 **********************************************************/
int two_or_four();


/**********************************************************
 *   Initialization
 **********************************************************/
Board empty_board() {
    Board b = (Board)malloc(sizeof(struct board_data));
    b->data = (int *)calloc(BOARDSIZE * BOARDSIZE, sizeof(int));
    if (b == NULL) {
        fprintf(stderr, "Malloc failed to allocate board\n");
        exit(1);
    }
    return b;
}
void free_board(Board b) {
    free(b->data);
    free(b);
}

/**********************************************************
 *   Accessors + Mutators
 **********************************************************/
int bget(Board b, int row, int col) {
    return *(b->data + row * BOARDSIZE + col);
}
void place(Board b, int row, int col, int val) {
    *(b->data + row * BOARDSIZE + col) = val;
}
void place_rand(Board b) {
    PointList pl = open_spaces(b);
    Point p = pl_rand(pl);
    if (p == NULL) {
        fprintf(stderr, "Number not placed, board is full.\n");
        return;
    }
    place(b, p->r, p->c, two_or_four());
}

PointList open_spaces(Board b) {
    PointList pl = pl_create();
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            if (bget(b, r, c) == 0)
                pl_insert(pl, r, c);
        }
    }
    return pl;
}


int is_valid_move(Board b, Move m) {
    return 1;
}

Move *valid_moves(Board b, int *size) {
    int cnt = 0;
    Move *moves = calloc(NUM_MOVES, sizeof(Move));
    for (int m=Up; m<=Right; m++) {
        if (is_valid_move(b, m)) {
            moves[cnt] = m;
            cnt++;
        }
    }
    *size = cnt;
    if (size == 0) {
        free(moves);
        return NULL;
    }
    return moves;
}


void shift(Board b, Move m) {
    /*
    Board tmp = rotate_for_move(b, m);

    Board tmp2 = invert_rotate_for_move(tmp, m);
    int **old = b->data;
    b->data = tmp2->data;
    free_board(tmp);
    free(tmp2); // DO NOT FREE tmp2->data
    free(old);
     */
}


/**********************************************************
*   Printing
**********************************************************/
void print_horizontal() {
    for (int i=0; i < (BOARDSIZE*NUMCHARS)+2; i++) {
        printf("-");
    }
    printf("\n");
}
void print_board(Board b) {
    print_horizontal();
    for (int r=0; r < BOARDSIZE; r++) {
        printf("|");
        for (int c=0; c < BOARDSIZE; c++) {
            int val = bget(b, r,c);
            for (int i=0; i < NUMCHARS - num_digits(val); i++)
                printf(" "); // Right-justify numbers
            printf("%d", val);
        }
        printf("|\n");
    }
    print_horizontal();
}

/**********************************************************
 *   Randomness
 **********************************************************/
/*
 * Returns 2 with probability 0.9, 4 with probability 0.1 (same as orignal game)
 */
int two_or_four() {
    int x = randint(10);
    if (x == 0)
        return 4;
    return 2;
}

/**********************************************************
 *   Board Rotation
 **********************************************************/
Board rotate_for_move(Board og, Move m) {
    Board b = empty_board();
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            switch (m) {
                case Up:
                    place(b, c, BOARDSIZE-1-r, bget(og,r,c));
                    break;
                case Down:
                    place(b, BOARDSIZE-1-c, r, bget(og,r,c));
                    break;
                case Left:
                    place(b, r, BOARDSIZE-1-c, bget(og,r,c));
                    break;
                case Right:
                    place(b, r, c, bget(og,r,c));
                    break;
                default:
                    break;
            }
        }
    }
    return b;
}
Board invert_rotate_for_move(Board og, Move m) {
    Board b = empty_board();
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            switch (m) {
                case Up:
                    place(b, r, c, bget(og, c, BOARDSIZE-1-r));
                    break;
                case Down:
                    place(b, r, c, bget(og, BOARDSIZE-1-c, r));
                    break;
                case Left:
                    place(b, r, c, bget(og, r, BOARDSIZE-1-c));
                    break;
                case Right:
                    place(b, r, c, bget(og, r, c));
                    break;
                default:
                    break;
            }
        }
    }
    return b;
}



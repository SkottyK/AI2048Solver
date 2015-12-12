//
//  heuristics.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/7/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include "heuristics.h"

double sum_heuristic(Board b) {
    int sum = 0;
    for (int r=0; r<BOARDSIZE; r++)
        for (int c=0; c<BOARDSIZE; c++)
            sum += bget(b, r, c);
    return (double)sum;
}

double squaresum_heuristic(Board b) {
    int sum = 0;
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            int this = bget(b, r, c);
            sum += this * this;
        }
    }
    return (double)sum;
}

double weights[BOARDSIZE][BOARDSIZE] = {
    { 0, 1, 2, 3},
    { 4, 5, 6, 7},
    { 8, 9,10,11},
    {12,13,14,15}
};
double weighted_sum1(Board b) {
    double sum = 0.0;
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            int this = bget(b, r, c);
            sum += (double)(this * this) * weights[r][c];
        }
    }
    return sum;
}

double weighted_sum2(Board b) {
    int sum = 0;
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            int this = bget(b, r, c);
            sum += this * this * (r + c);
        }
    }
    return (double)sum;
}

double empty_blocks(Board b) {
    PointList pl = open_spaces(b);
    if (pl == NULL) {
        return 0;
    }
    int num_blocks = pl->N;
    pl_free(pl);
    return (double)num_blocks;
}

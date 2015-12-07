//
//  heuristics.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/7/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include "heuristics.h"

int sum_heuristic(Board b) {
    int sum = 0;
    for (int r=0; r<BOARDSIZE; r++)
        for (int c=0; c<BOARDSIZE; c++)
            sum += bget(b, r, c);
    return sum;
}


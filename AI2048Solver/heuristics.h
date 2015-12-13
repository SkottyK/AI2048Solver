//
//  heuristics.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/7/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef heuristics_h
#define heuristics_h

#include <stdio.h>
#include "board.h"

typedef double (*Heuristic)(Board B);

double sum_heuristic(Board b);
double squaresum_heuristic(Board b);
double weighted_sum1(Board b);
double weighted_sum2(Board b);
double empty_blocks(Board b);

#endif /* heuristics_h */

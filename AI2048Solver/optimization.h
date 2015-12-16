//
//  optimization.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/10/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef optimization_h
#define optimization_h

#include <stdlib.h>
#include "board.h"

typedef struct opt_data {
    int theta[BOARDSIZE * BOARDSIZE];
    float average;
} opt_data;

opt_data *stoch_opt(int num_iterations, int num_avg);
opt_data *optimize_score(int num_iterations);
opt_data *grid_opt(int num_iterations);

#endif /* optimization_h */

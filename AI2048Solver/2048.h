//
//  2048.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/24/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef _048_h
#define _048_h

#include <stdio.h>
#include "game.h"

/* Play game on command line */
void human_game();

void test_suite(int argc, const char *argv[]);
void test_minimax(Heuristic h, int *score, int *maxtile);
void test_expectation(Heuristic h, int depth, int *score, int *maxtile);

#endif /* _048_h */

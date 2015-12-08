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
void play2048(Game g);

void human_game();

void baseline(int num_trials);

#endif /* _048_h */

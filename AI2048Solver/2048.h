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

typedef enum move_directions {
    Up,
    Down,
    Left,
    Right
} Move;

typedef struct point_data {
    int r;
    int c;
} *Point;

#endif /* _048_h */

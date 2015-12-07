//
//  num_util.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include "num_util.h"

int num_digits(int x) {
    int count = 1;
    int div = 10;
    while (x / div) {
        div *= 10;
        count++;
    }
    return count;
}

/*
 * Returns random number [0, n)
 *
 * CITE: The following function is based upon the `randint` function provided
 * by Laurence Gonsalves in a StackOverflow post here:
 *http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
 */
int randint(int n) {
    if ((n - 1) == RAND_MAX) {
        return rand();
    } else {
        int r;
        long end = RAND_MAX / n;
        end *= n;
        while ((r = rand()) >= end);
        
        return r % n;
    }
}


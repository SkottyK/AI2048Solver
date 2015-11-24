//
//  num_util.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

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

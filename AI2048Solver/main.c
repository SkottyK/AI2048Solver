//
//  main.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdio.h>
#include "board.h"

int main(int argc, const char * argv[]) {

    Board b = empty_board();

    set(b, 0, 0, 1);
    set(b, 0, 2, 2);

    print_board(B);

    return 0;
}

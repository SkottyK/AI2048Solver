//
//  main.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/21/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "point.h"



int test_rotate() {
    Board b = empty_board();

    for (int r=0; r<4; r++) {
        for (int c=0; c<4; c++) {
            place(b, r, c, (r+1) * 10 + (c+1));
        }
    }
    assert(pl_empty(open_spaces(b)));

    Board tmp, tmp2;
    printf("Original:\n");
    print_board(b);


    printf("\nRotate for up:\n");
    tmp = rotate_for_move(b, Up);
    tmp2 = invert_rotate_for_move(tmp, Up);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);


    printf("\nRotate for down:\n");
    tmp = rotate_for_move(b, Down);
    tmp2 = invert_rotate_for_move(tmp, Down);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);


    printf("\nRotate for left:\n");
    tmp = rotate_for_move(b, Left);
    tmp2 = invert_rotate_for_move(tmp, Left);
    print_board(tmp);
    printf("Back to normal:\n");
    print_board(tmp2);
    free(tmp);
    free(tmp2);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    return test_rotate();
}

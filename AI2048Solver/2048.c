//
//  2048.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 11/24/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "2048.h"
#include "game.h"
#include "board.h"

void play2048(Game g) {
    while(!is2048(g->board)) {
        int* size = (int*)malloc(sizeof(int));
        Move* moves = effectual_moves(g->board, size);
        if (moves == NULL) {
            printf("No more moves, game over!\n");
        }
        int i;
        for (i = 0; i < *size; i++) {
            
        }
        
        
        
    }
}
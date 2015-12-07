//
//  point.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/6/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include "point.h"
#include "num_util.h"


/****************************************
 * Point
 ****************************************/
int pt_eq(Point p1, Point p2) {
    return (p1->r == p2->r) && (p1->c == p2->c);
}
int pt_eqrc(Point p, int r, int c) {
    return (p->r == r) && (p->c == c);
}


/****************************************
 * Point List
 ****************************************/
typedef struct pnode_data {
    Point p;
    struct pnode_data *next;
} *pnode;

struct point_list_data {
    int N;
    pnode root;
};


PointList pl_create() {
    PointList pl = malloc(sizeof(struct point_list_data));
    pl->N = 0;
    pl->root = NULL;
    return pl;
}
void pl_free(PointList pl) {
    pnode node = pl->root;
    while (node != NULL) {
        pnode next = node->next;
        free(node->p);
        free(node);
        node = next;
    }
}

int pl_empty(PointList pl) {
    return pl->N == 0;
}

int pl_contains(PointList pl, int r, int c) {
    pnode node = pl->root;
    while (node != NULL) {
        if (pt_eqrc(node->p, r, c))
            return 1;
        node = node->next;
    }
    return 0;
}

void pl_insert(PointList pl, int r, int c) {
    Point p = malloc(sizeof(struct point_data));
    p->r = r;
    p->c = c;
    pnode node = malloc(sizeof(struct pnode_data));
    node->p = p;
    node->next = pl->root;
    pl->root = node;
    pl->N++;
}

Point pl_rand(PointList pl) {
    if (pl_empty(pl)) {
        return NULL;
    }
    int target = randint(pl->N);
    int i = 0;
    pnode node = pl->root;
    while(i < target) {
        node = node->next;
        i++;
    }
    return node->p;
}




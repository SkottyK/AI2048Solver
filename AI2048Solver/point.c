//
//  point.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/6/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#include <stdlib.h>
#include "list.h"
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
struct point_list_data {
    int N;
    list points;
};


PointList pl_create() {
    PointList pl = malloc(sizeof(struct point_list_data));
    pl->N = 0;
    list_new(&(pl->points), sizeof(struct point_data), free);
    return pl;
}
void pl_free(PointList pl) {
    list_destroy(&(pl->points));
    free(pl);
}

int pl_empty(PointList pl) {
    return pl->N == 0;
}

int pl_size(PointList pl) {
    return pl->N;
}

int pl_contains(PointList pl, int r, int c) {
    listNode *node = pl->points.head;
    while (node != NULL) {
        Point p = (Point)node->data;
        if (pt_eqrc(p, r, c))
            return 1;
        node = node->next;
    }
    return 0;
}

void pl_insert(PointList pl, int r, int c) {
    Point p = malloc(sizeof(struct point_data));
    p->r = r;
    p->c = c;
    list_prepend(&pl->points, (void *)p);
    pl->N++;
}

Point pl_rand(PointList pl) {
    if (pl_empty(pl)) {
        return NULL;
    }
    int target = randint(pl->N);
    int i = 0;
    listNode *node = pl->points.head;
    while(i < target) {
        node = node->next;
        i++;
    }
    return (Point)node->data;
}




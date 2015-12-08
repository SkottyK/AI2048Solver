//
//  point.h
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/6/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//

#ifndef point_h
#define point_h

#include <stdio.h>
#include "list.h"

typedef struct point_data {
    int r;
    int c;
} *Point;

int pt_eq(Point p1, Point p2);
int pt_eqrc(Point p, int r, int c);

struct point_list_data {
    int N;
    list points;
};
typedef struct point_list_data *PointList;

PointList pl_create();
void pl_free(PointList pl);

int pl_empty(PointList pl);
int pl_size(PointList pl);
int pl_contains(PointList pl, int r, int c);
void pl_insert(PointList pl, int r, int c);

Point pl_rand(PointList pl);

#endif /* point_h */

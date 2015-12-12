//
//  optimization.c
//  AI2048Solver
//
//  Created by Scott Krulcik on 12/10/15.
//  Copyright © 2015 Scott Krulcik. All rights reserved.
//
#include <string.h>
#include <math.h>
#include "nlopt.h"
#include "optimization.h"
#include "2048.h"

#define DIM (BOARDSIZE * BOARDSIZE)
#define TIMEOUT 900.0
#define MAX_OPT_EVAL 1000

typedef struct custom_data {
    int num_iterations;
} custom_data;


double theta[DIM];
int runs = 0;
int theta_weight(Board b) {
    int sum = 0;
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            int this = bget(b, r, c);
            sum += (double)(this * this) * theta[r * BOARDSIZE + c];
        }
    }
    return (int)(sum * 100);
}


double average_score(unsigned n, const double *theta, double *grad, void* f_data) {
    custom_data *data = (custom_data *)f_data;
    double multiplier = 1.0 / (double)data->num_iterations;
    double average = 0.0;
    int score;

    for (int i = 0; i < data->num_iterations; i++) {
        test_heuristic(&theta_weight, &score, NULL);
        average += (double)score * multiplier;
    }

    runs++;
    printf("%d,%.3f\n", runs, average);

    return average;
}

double sum0(unsigned n, const double *theta, double *grad, void *f_data) {
    double sum = 0;
    double epsilon = 0.001;
    for (int i = 0; i < n; i++)
        sum += theta[i];
    return (sum < epsilon && sum > -epsilon) ? 0:-1;
}




opt_data *optimize_score(int num_iterations) {
    double average = 0.0;
    custom_data function_data;
    function_data.num_iterations = num_iterations;
    nlopt_opt opt = nlopt_create(NLOPT_LN_COBYLA, DIM);

    // Initialize theta to all zeroes
    memset(&theta, 0, DIM);
    nlopt_set_max_objective(opt, &average_score, &function_data);
    nlopt_set_lower_bounds1(opt, -1.0);
    nlopt_set_upper_bounds1(opt, 1.0);
    nlopt_set_maxtime(opt, TIMEOUT);

    double max_avg;
    nlopt_result result = nlopt_optimize(opt, theta, &max_avg);
    if (result < 0) {
        printf("ERROR optimizing: %d\n", result);
        exit(1);
    } else if (result == 5) {
        printf("Terminated by reaching max eval.\n");
    } else if (result == 6) {
        printf("Terminated by reaching max time.\n");
    }
    printf("Final Optimization Weights:\n");
    for (int r = 0; r < BOARDSIZE; r++) {
        printf("[");
        for (int c = 0; c < BOARDSIZE; c++) {
            printf("%6.3f", theta[r * BOARDSIZE + c]);
        }
        printf("]\n");
    }
    printf("\n");
    printf("Optimized average score: %.3f\n", max_avg);

    opt_data *data = (opt_data *)malloc(sizeof(opt_data));
    data->average = average;
    memcpy(&data->theta, &theta, DIM);
    return data;
}





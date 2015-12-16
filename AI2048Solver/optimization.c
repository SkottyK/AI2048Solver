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
double theta_weight(Board b) {
    double sum = 0;
    for (int r=0; r<BOARDSIZE; r++) {
        for (int c=0; c<BOARDSIZE; c++) {
            int this = bget(b, r, c);
            sum += (double)(this * this) * theta[r * BOARDSIZE + c];
        }
    }
    return sum;
}


double average_score(unsigned n, const double *theta, double *grad, void* f_data) {
    custom_data *data = (custom_data *)f_data;
    double multiplier = 1.0 / (double)data->num_iterations;
    double average = 0.0;
    int score;

    for (int i = 0; i < data->num_iterations; i++) {
        test_minimax(&theta_weight, &score, NULL);
        average += (double)score * multiplier;
    }

    runs++;
    if (!(runs % 1000))
        printf("%d,%.3f\n", runs, average);

    return average;
}

double track_average(unsigned n, const double *theta, double *grad, void* f_data) {
    custom_data *data = (custom_data *)f_data;
    double multiplier = 1.0 / (double)data->num_iterations;
    double average = 0.0;
    int score;
    double averages[data->num_iterations/10];

    for (int i = 0; i < data->num_iterations; i++) {
        test_minimax(&theta_weight, &score, NULL);
        average += (double)score * multiplier;
        if (i % 10 == 0) {
            averages[i / 10] = average * ((double)data->num_iterations / i);
        }
    }
    printf("iter,difference\n");
    for (int i = 0; i < data->num_iterations/10; i++) {
        printf("%3d0,%5.3f\n", i, (averages[i] - average)/average);
    }
    printf("\n");

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

opt_data *stoch_opt(int num_iterations, int num_avg) {
    custom_data function_data;
    function_data.num_iterations = num_avg;
    int r_per_s = 1;
    double start_step = 8.0;
    double average = 0.0, step = start_step;

    for (int testcount = 0; testcount < num_iterations; testcount++) {
        int i = testcount % DIM; // Index of param to optimize
        double *param = &(theta[i]);
        double tests[3] = { theta[i] - step, theta[i], theta[i] + step };
        double best_test = 0.0, best_average = 0.0;
        for (int ti = 0; ti < 3; ti++) {
            *param = tests[ti];
            average = average_score(DIM, theta, NULL, &function_data);
            if (average > best_average) {
                best_average = average;
                best_test = tests[ti];
            }
        }
        *param = (best_test + *param) / 2;
        average = best_average;

        if (testcount % (DIM * r_per_s) == 0 && testcount != 0) {
            step = step - (start_step / ((double)num_iterations / (DIM * r_per_s)));
            printf("%5d [", testcount);
            for (int idx = 0; idx < DIM; idx++) {
                printf("%6.2f", theta[idx]);
            }
            printf("] %8.0f  %f\n", best_average, step);
        }
    }
    printf("END [");
    for (int idx = 0; idx < DIM; idx++) {
        printf("%6.2f", theta[idx]);
    }
    printf("] %8.0f\n", average);



    opt_data *data = malloc(sizeof(opt_data));
    function_data.num_iterations = 250;
    data->average = average_score(DIM, theta, NULL, &function_data);
    memcpy(&data->theta, theta, DIM);
    return data;
}


opt_data *grid_opt(int num_iterations) {
    double start[DIM], step = 1.0;
    int mods[DIM], avgidx[DIM], num_samples = 3, num_shrinks = 3;
    int max_count = (int)pow(DIM, num_samples);
    double average[DIM][num_samples];
    custom_data function_data;
    function_data.num_iterations = num_iterations;

    memset(&theta, 0x0, DIM);

    for (int i = 0; i < DIM; i++)
        start[i] = -1.0;
    mods[0] = num_samples;
    for (int i = 1; i < DIM; i++)
        mods[i] = mods[i-1] * num_samples;

    for (int i = 0; i < num_shrinks; i++) {
        for (int counter = 0; counter < max_count; counter++) {
            for (int j = 0; j < DIM; j++) {
                if (counter % mods[j] == 0) {
                    avgidx[j] = (avgidx[j] + 1) % num_samples;
                    theta[j] += step;
                }
                average[j][avgidx[j]] = average_score(DIM, theta, NULL, &function_data) / ((double)counter);
            }
        }
        for (int j = 0; j < DIM; j++) {
            double subavg[num_samples - 1];
            memset(subavg, 0, num_samples - 1);
            for (int k = 0; k < num_samples - 1; k++) {
                subavg[k] += average[j][k] / ((double)num_samples - 1);
            }
            double max = 0.0;
            int best_start = 0;
            for (int k = 0; k < num_samples -1 ; k++) {
                if (subavg[k] > max) {
                    best_start = k;
                    max = subavg[k];
                }
            }
            start[j] = start[j] + (double)best_start * step;
        }
        step /= 2.0;
        printf("Start:\n[");
        for (int j = 0; j < DIM; j++)
            printf(" %5.3f", start[j]);
        printf("]\n");
    }
    double avgall = 0.0;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < num_samples; j++)
            avgall += average[i][avgidx[j]];
    opt_data *data = (opt_data *)malloc(sizeof(opt_data));
    data->average = avgall;
    memcpy(&data->theta, &theta, DIM);
    return data;
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




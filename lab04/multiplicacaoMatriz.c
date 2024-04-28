#include <pthread.h>
#include <stdio.h>

int m = 4;
int n = 3;
double A[4][3] = {{2, 2, 3}, {4, 3, 6}, {4, 4, 9}, {5, 11, 6}};
double x[3] = {1, 3, 4};
double y[4]; 
int thread_count = 4;


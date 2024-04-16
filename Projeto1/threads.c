#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct EscadaArgs{
    int n;
    int* t;
    int* direcoes;
} EscadaArgs;



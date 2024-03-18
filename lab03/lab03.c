#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

#define FIBER_STACK 1024*64
volatile int var_compartilhada = 0;

int threadFunction(void* argument) {
    
    while(var_compartilhada == 0){
        usleep(100);
    }
    printf("Filho: Recebi a mensagem!\n");

    var_compartilhada = 2;

    return 0;
}

int main() {
    void* stack;
    pid_t pid;

    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: Could not allocate stack");
        exit(1);
    }

    printf("Thread filho eh criado\n");

    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if (pid == -1) {
        perror("Erro no clone");
        exit(2);
    }


    var_compartilhada = 1;
    printf("Pai: Enviei a mensagem!\n");

    while(var_compartilhada != 2){
        usleep(100);
    }
    printf("Pai: Filho confirmou o recebimento da mensagem.\n");

    pid = waitpid(pid, NULL, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    free(stack);
    printf("Thread filho retornado e pilha liberada.\n");
    return 0;
}

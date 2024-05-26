#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h> // Inclui a biblioteca de mutex
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

// 64kB stack
#define FIBER_STACK 1024 * 64

struct c {
    int saldo;
};
typedef struct c conta;
conta from, to;
int valor;
pthread_mutex_t lock; // Declara um mutex

struct transfer {
    conta *from;
    conta *to;
    int valor;
    const char *direcao;
    const char *from_label;
    const char *to_label;
};

// A função executada pela thread filha
void* transferencia(void *arg) {
    struct transfer *args = (struct transfer *)arg;
    pthread_mutex_lock(&lock); // Trava o mutex para garantir acesso exclusivo
    if (args->from->saldo >= args->valor) { // Verifica se há saldo suficiente
        args->from->saldo -= args->valor;     // Subtrai o valor da conta 'from'
        args->to->saldo += args->valor;       // Adiciona o valor à conta 'to'
        printf("Transferência realizada com sucesso (%s)!\n", args->direcao);
    } else {
        printf("Não é possível enviar dinheiro por saldo insuficiente (%s)!\n", args->direcao);
    }
    printf("Saldo de c1(%s): %d\n", args->from_label, args->from->saldo);
    printf("Saldo de c2(%s): %d\n", args->to_label, args->to->saldo);
    pthread_mutex_unlock(&lock); // Destrava o mutex
    free(arg); // Libera a memória alocada para os argumentos
    return NULL;
}

void trocarContas(const char **direcao, const char **from_label, const char **to_label) {
    pthread_mutex_lock(&lock); // Travar o mutex para garantir o acesso exclusivo
    conta aux = from;
    from = to;
    to = aux;
    pthread_mutex_unlock(&lock); // Destravar o mutex
    *direcao = "To → From";
    *from_label = "to";
    *to_label = "from";
}

int main() {
  //  struct transfer *args = (struct transfer *)arg;
    int i;

    // Inicializa o mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Falha mutex_init");
        exit(1);
    }

    // Inicializa os saldos das contas
    from.saldo = 100;
    to.saldo = 100;
    printf("Saldo de from: %d\n", from.saldo);
    printf("Saldo de to: %d\n", from.saldo);
    printf("Transferindo 100 para a conta c2 (1 vez)\n");
  //  printf("Saldo de c1(%s): %d\n", args->from_label, args->from->saldo);
  //  printf("Saldo de c2(%s): %d\n", args->to_label, args->to->saldo);
    valor = 100;

    int transferCount = 0;
    const char *direcao = "From → To";
    const char *from_label = "from";
    const char *to_label = "to";

    // Cria 5 threads para realizar transferências
    for (i = 0; i < 5; i++) {
        if (from.saldo < valor) {
            printf("Saldo insuficiente para realizar mais transferências. Interrompendo...\n");
            break;
        }
        struct transfer *args = malloc(sizeof(struct transfer));
        if (args == NULL) {
            perror("Não foi possível alocar memória");
            exit(1);
        }
        args->from = &from;
        args->to = &to;
        args->valor = valor;
        args->direcao = direcao;
        args->from_label = from_label;
        args->to_label = to_label;

        pthread_t thread;
        if (pthread_create(&thread, NULL, transferencia, (void*)args) != 0) {
            perror("pthread_create");
            exit(2);
        }
        pthread_join(thread, NULL); // Espera a thread atual terminar antes de criar a próxima
        transferCount++;

        // Troca as contas após cada 5 transferências
        if (transferCount % 5 == 0) {
            printf("Transferências concluídas!\n");
            printf("Saldo de c1(%s): %d\n", from_label, from.saldo);
            printf("Saldo de c2(%s): %d\n", to_label, to.saldo);
            if (from.saldo == 0 || to.saldo == 0) {
                trocarContas(&direcao, &from_label, &to_label);
                printf("---------------------------------------------------\n");
                printf("Contas Trocadas. Transferindo 20 %s (5 vezes)\n", direcao);
            }
        }

        // Para quando as transferências completarem o ciclo
        if (from.saldo == 100 && to.saldo == 100) {
            break;
        }
    }

    // Destrói o mutex
    pthread_mutex_destroy(&lock);

    // Exibe os saldos finais
    printf("Transferências concluídas!\n");
    printf("Saldo de c1(%s): %d\n", from_label, from.saldo);
    printf("Saldo de c2(%s): %d\n", to_label, to.saldo);

    return 0;
}

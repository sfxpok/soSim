// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <string.h>

// Estruturas de dados

struct shop {
    int maxClients;
    int spawnedClients;
    int avgTimeArrivalClients;
    int openingTime;
    int closingTime;
    int timeCounter;
    int isItOpen;
    int durationOpen;
};

struct stats {
    int soldItems;
    int totalWithdrawls;
};

// Threads

// pthread_t threadClient;

// Inicializações

struct shop simulador;
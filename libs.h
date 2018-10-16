// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>

// Estruturas de dados

struct shop {
    int maxClients;
    int spawnedClients;
    int openingTime;
    int closingTime;
    int timeCounter;
    int isItOpen;
    int durationOpen;
};

struct shop simulador;

// Outros

pthread_t threadClient;
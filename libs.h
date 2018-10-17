// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <string.h>

// Estruturas de dados

struct shop {
    int maxClients;
    int maxEmployees;
    int maxClientsPerEmployee;
    int spawnedClients;
    int timeToServePonchaA;
    int timeToServePonchaB;
    int timeToServePonchaC;
    int unitsPonchaA;
    int unitsPonchaB;
    int unitsPonchaC;
    int replacersProducts;
    int probChangeOrder;
    int probWithdrawl;
    int openingTime;
    int closingTime;
    int timeCounter;
    int isItOpen;
};

struct stats {
    int totalWithdrawls;
    int durationOpen;
    int avgTimeArrivalClients;
    int totalClients;
    int waitingClientsInLine;
    int avgTimeWaitingClientsInLine;
    int totalChangedOrder;
    int maxEmployeesUsed;
    int actualEmployeesUsedNow;
    int unitsSoldPonchaA;
    int unitsSoldPonchaB;
    int unitsSoldPonchaC;
    int avgTimeToServePonchaA;
    int avgTimeToServePonchaB;
    int avgTimeToServePonchaC;
};

// Threads

// pthread_t threadClient;

// Inicializações

struct shop simulador;
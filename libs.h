// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <string.h>
#include <time.h> 

// Variáveis

char messageToLog[128];
char* writeToLog;
FILE* logFile;

time_t     UNIXts;
struct tm  ts;
char       hmsTimeStamp[80];

// Estruturas de dados

struct shop {
    int maxClients;
    int maxEmployees;
    int maxClientsPerEmployee;
    int spawnedClients;
    int timeToServePonchaA; // importante para inicialização
    int timeToServePonchaB; // importante para inicialização
    int timeToServePonchaC; // importante para inicialização
    int unitsPonchaA;
    int unitsPonchaB;
    int unitsPonchaC;
    int replacersProducts;
    int probChangeOrder;
    int probWithdrawl; // importante para inicialização
    int openingTime;
    int closingTime;
    int timeCounter;
    int isItOpen;
};

struct stats {
    int totalWithdrawls;
    int avgTimeArrivalClients; // importante para inicialização
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
    int durationOpen; // importante para inicialização
};

// Threads

// pthread_t threadClient;

// Inicializações

struct shop simulador;
struct stats estatistica;
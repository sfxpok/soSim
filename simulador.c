#include "libs.h"

#define MAXFILE 128

void readConfig() {

    FILE * fileConfig = fopen("config.conf", "r");

    char param[MAXFILE];
    int value;

    // Valores pré-definidos
    simulador.maxClients = 3;
    simulador.spawnedClients = 6;
    simulador.openingTime = 10;
    simulador.closingTime = 13;
    simulador.timeCounter = 0;
    simulador.isItOpen = 1;
    // simulador.durationOpen = 0;

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");
    }

    else {
        printf("A ler o ficheiro de configuração...\n");

        while(fscanf(fileConfig, "%s %d\n", param, &value) != EOF) {

            if (strcmp(param, "maxClients") == 0) simulador.maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0) simulador.spawnedClients = value;
            // else if (strcmp(param, "avgTimeArrivalClients") == 0) simulador.avgTimeArrivalClients = value;
            else if (strcmp(param, "openingTime") == 0) simulador.openingTime = value;
            else if (strcmp(param, "closingTime") == 0) simulador.closingTime = value;
            else if (strcmp(param, "timeCounter") == 0) simulador.timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0) simulador.isItOpen = value;
            // else if (strcmp(param, "durationOpen") == 0) simulador.durationOpen = value;

        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
        
    }

}

void writeOutputToMonitor() {
    //
}

void main () {
    readConfig();
}

/* int clientTID;
int clientTID2;

void* computeClient(void* ptr) {
    printf("test\n");
}

void createClient() {

    clientTID = pthread_create(&threadClient, 0, computeClient, 0);
    clientTID2 = pthread_create(&threadClient, 0, computeClient, 0);

    printf("%d\n", clientTID);
    printf("%d\n", clientTID2);

} */
#include "libs.h"

#define MAXFILE 128

void main () {
    readConfig();
}

void readConfig() {

    // FILE *fileConfig = fopen("/home/r/git/soSim/config.conf","r");

    FILE *fileConfig;
    char* filename = "/home/r/git/soSim/config.conf";
    fileConfig = fopen(filename, "r");

    char line[256];
    char param[MAXFILE];
    int value;

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos."); // FALTA DEFINIR
    }

    else {
        printf("A ler o ficheiro de configuração...\n");

        while(fscanf(fileConfig, "%s: %d\n", param, &value) != EOF) {

            if (strcmp(param, "maxClients") == 0) simulador.maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0) simulador.spawnedClients = value;
            else if (strcmp(param, "openingTime") == 0) simulador.openingTime = value;
            else if (strcmp(param, "closingTime") == 0) simulador.closingTime = value;
            else if (strcmp(param, "timeCounter") == 0) simulador.timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0) simulador.isItOpen = value;
            else if (strcmp(param, "durationOpen") == 0) simulador.durationOpen = value;

        }

/*      char buf[0x1000];
        struct shop a_shop[500];

        while (fgets(buf, sizeof(buf), fileConfig) != NULL) {
            if (buf[0] == '#') {
                continue;
            }
            else {
                fscanf(fileConfig, "%d", &a_shop.maxClients);
            }

        } */

        fclose(fileConfig);
        printf("Inicialização feita.\n");
        printf("%d", simulador.spawnedClients);
        printf("%d", simulador.openingTime);
        
    }

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
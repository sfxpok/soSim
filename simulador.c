#include "libs.h"

#define MAXFILE 128

void readConfig() {

    FILE * fileConfig = fopen("config.conf", "r");

    char param[MAXFILE];
    int value;

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");

        // Valores pré-definidos
        simulador.maxClients = 3;
        simulador.spawnedClients = 6;
        estatistica.avgTimeArrivalClients = 3;
        simulador.timeToServePonchaA = 2;
        simulador.timeToServePonchaB = 3;
        simulador.timeToServePonchaC = 4;
        simulador.probWithdrawl = 2;
        simulador.openingTime = 10;
        simulador.closingTime = 13;
        simulador.timeCounter = 0;
        simulador.isItOpen = 1;
        estatistica.durationOpen = 0;
    }

    else {
        printf("A ler o ficheiro de configuração...\n");

        while(fscanf(fileConfig, "%s %d\n", param, &value) != EOF) {

            if (strcmp(param, "maxClients") == 0) simulador.maxClients = value;
            else if (strcmp(param, "spawnedClients") == 0) simulador.spawnedClients = value;
            else if (strcmp(param, "avgTimeArrivalClients") == 0) estatistica.avgTimeArrivalClients = value;
            else if (strcmp(param, "timeToServePonchaA") == 0) simulador.timeToServePonchaA = value;
            else if (strcmp(param, "timeToServePonchaB") == 0) simulador.timeToServePonchaB = value;
            else if (strcmp(param, "timeToServePonchaC") == 0) simulador.timeToServePonchaC = value;
            else if (strcmp(param, "probWithdrawl") == 0) simulador.probWithdrawl = value;
            else if (strcmp(param, "openingTime") == 0) simulador.openingTime = value;
            else if (strcmp(param, "closingTime") == 0) simulador.closingTime = value;
            else if (strcmp(param, "timeCounter") == 0) simulador.timeCounter = value;
            else if (strcmp(param, "isItOpen") == 0) simulador.isItOpen = value;
            else if (strcmp(param, "durationOpen") == 0) estatistica.durationOpen = value;

        }

        fclose(fileConfig);
        printf("Inicialização feita.\n");
    }

}

void writeOutputToMonitor() {
    //
}

void* computeClient(void* ptr) {
    //
}

void createClient(int idCliente) {

    printf("Cliente %d acabou de chegar.", idCliente);

}

void giveUpClient(int idCliente) {

    printf("Cliente %d desistiu.", idCliente);

}

void askForPoncha(int idCliente, char charPoncha) {

    switch (charPoncha) {
        case 'a':
            // da-lhe poncha A
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
        case 'b':
            // da-lhe poncha B
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
        case 'c':
            // da-lhe poncha C
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
    }

}

void givePonchaToClient(int idCliente, char chaPoncha, int idEmployee) {
    //
}

void changeOrder() {
    //
}

void writeLogFiles() {
    //
}

void appendFinalReport() {
    //
}

void restockProduct(int idCliente, char charPoncha) {

    switch (charPoncha) {
        case 'a':
            // repoe poncha A
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
        case 'b':
            // repoe poncha B
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
        case 'c':
            // repoe poncha C
            printf("O cliente %d pediu pela poncha %c", idCliente, charPoncha);
            break;
    }

}

void addEmployeeToCashier(int idEmployee) {
    //
}

void checkIfProductIsOutOfStock(char charPoncha) {
    //
}

void main () {
    readConfig();

    // começa a simulação

}
#include "libs.h"

void initSimulation() {
    readConfig();
    cleanLogFile();
}

void cleanLogFile() {

    FILE * logFile = fopen("log.txt", "w"); // A flag "w" cria um novo ficheiro de raíz
    fclose(logFile);

}

void readConfig() {

    FILE * fileConfig = fopen("config.conf", "r");

    char param[128];
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

void createClient(int idCliente) {

    // printf("O cliente %d acabou de chegar.\n", idCliente);
    snprintf(messageToLog, sizeof(messageToLog), "O cliente %d acabou de chegar.\n", idCliente);
    writeLogFiles(messageToLog);

}

void createEmployee(int idEmployee) {
    
    // printf("O empregado %d chegou à loja.", idEmployee);
    snprintf(messageToLog, sizeof(messageToLog), "O empregado %d chegou à loja.", idEmployee);
    writeLogFiles(messageToLog);

}

void calculateRunningTimeShop() {
    
    estatistica.durationOpen = (simulador.closingTime - simulador.openingTime) * 60;

    snprintf(messageToLog, sizeof(messageToLog), "A loja está aberta durante %d minutos.\n", estatistica.durationOpen);
    writeLogFiles(messageToLog);
    
}

char* getTimeStamp() {

    // Get current time
    time(&UNIXts);

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&UNIXts);
    strftime(hmsTimeStamp, sizeof(hmsTimeStamp), "%H:%M:%S", &ts);
    return hmsTimeStamp;
}

void writeLogFiles(char* writeToLog) {
    
    FILE * logFile = fopen("log.txt", "a");
    
    char *timeStamp = getTimeStamp();
    fprintf(logFile, "%s %s", timeStamp, writeToLog);

    fclose(logFile);
}

void giveUpClient(int idCliente) {

    printf("Cliente %d desistiu.", idCliente);

}

void askForPoncha(int idCliente, char charPoncha) {

    switch (charPoncha) {
        case 'a':
            // da-lhe poncha A

            if (simulador.unitsPonchaA < 2) {
                // cliente espera
                break;
            }

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

void appendFinalReport() {
    //
}

void restockPoncha(int idCliente, char charPoncha) {

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

void moveEmployeeToCashier(int idEmployee) {
    //
}

void moveEmployeeToWarehouse(int idEmployee) {
    //
}

void checkIfProductIsOutOfStock(char charPoncha) {
    //
}

void main () {

    initSimulation();
    // readConfig();
    calculateRunningTimeShop();
    createClient(2);

}
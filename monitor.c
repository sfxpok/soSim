#include "libs.h"

void displayHeader() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                            Loja                             │\n");
    printf("│                Sistemas Operativos 2018/2019                │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

void displayMenu() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                      Lista de operacoes                     │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│        O comando é a primeira letra de cada operacao        │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│(i)nit - inicializa a simulacao                              │\n");
    printf("│(h)alt - pausa a simulacao                                   │\n");
    printf("│(q)uit - sai da simulacao                                    │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

void displayStats() {
    
}

void outputMenu() {

}

void pauseShop() {
    //
}

void closeShop() {
    printf("A loja foi fechada.\n");
}

void initThreads() {

    pthread_t tMonitor;
    // pthread_create(tMonitor, NULL, NULL, NULL);

    printf("PID do monitor: %d\n", getpid());

}

void askForInput() {

    char op;
    int halt = 0;

    do {

        printf("Escreva um comando:\n");
        scanf("%c", &op);

        switch(op) {

            case 'i':
                initThreads();
                break;
            
            case 'h':
                break;

            case 'q': // to be fixed
                halt = 1;
                break;
            
        }

        // e preciso mudar a condicao do while para o op, eventualmente
        // op = getchar();

    } while(halt != 1);

    closeShop();

}

void main() {
    displayHeader();
    displayMenu();
    askForInput();

    // initThreads();
}
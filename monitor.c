#include "libs.h"

void displayHeader() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                            Loja                             │\n");
    printf("│                    Sistemas Operativos 18/19                │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
}

void displayMenu() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                            Loja                             │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│                    Sistemas Operativos 18/19                │\n");
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
    //
}

void initThreads() {

    pthread_t tMonitor;
    // pthread_create(tMonitor, NULL, NULL, NULL);

}

void askForInput() {

    char op;

    do {

        printf("Escreva um comando:\n");
        scanf("%c", &op);

        switch(op) {

            case 'i':
                initThreads();
                break;
            
            case 'h':
                break;
            
        }

    } while((op = getchar()) != 'q');

}

void main() {
    displayHeader();
    displayMenu();

    // initThreads();
}
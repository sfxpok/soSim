#include "libs.h"

void main () {

}

void readConfig() {

    FILE * fileConfig = fopen("config.conf", "r");
    fileConfig = fopen("config.conf", "r");

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");
    }

    else {
        printf("A inicializar a simulação...");
        /* ler o ficheiro de configuração aqui */

        fclose(fileConfig);
        printf("Inicialização feita.");
        
    }

}
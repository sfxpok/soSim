#include "libs.h"

#define MAXFILE 128

void main () {
    readConfig();
}

void readConfig() {

    FILE * fileConfig = fopen("config.conf", "r");
    fileConfig = fopen("config.conf", "r");

    char line[256];
    char param[MAXFILE];
    int value;

    if (fileConfig == NULL) {
        printf("Erro ao abrir o ficheiro. O programa irá usar valores pré-definidos.");
    }

    else {
        printf("A ler o ficheiro de configuração...");

        while(fscanf(fileConfig, "%s: %d\n", param, &value) != EOF) {
            /* ler linha a linha aqui */
        }


        while (fgets(line, sizeof(line), fileConfig)) {
            printf("%s", line); 
        }

        fclose(fileConfig);
        printf("\nInicialização feita.");
        
    }

}
#include "libs.h"

/* int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
char *hello = "Hello from server"; 
 */
int monSocket;

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

    // põe qualquer coisa aqui para escrever no ficheiro de log dude

    // cuidado que esta função está incompleta
    
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                         Estatisticas                        │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Geral ###                                               │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Duração da simulação: %d                                     │\n", timeCounter);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Clientes ###                                            │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Clientes criados na simulação: %d                            │\n", createdClients);
    printf("│Clientes à espera na fila: %d                                │\n", clientsInLine);
    printf("│Tempo médio de espera em fila: %d                            │\n", avgTimeWaitingClientsInLine);
    printf("│Clientes que mudaram o seu pedido: %d                        │\n", totalChangedOrder);
    printf("│Clientes que desistiram: %d                                  │\n", totalWithdrawls);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Empregados ###                                          │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Empregados ao serviço no máximo: %d                          │\n", maxEmployeesUsed);
    printf("│Empregados ao serviço: %d                                    │\n", actualEmployeesUsedNow);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│ ### Produtos ###                                            │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    printf("│Vendas do produto 1: %d                                      │\n", unitsSoldPonchaA);
    printf("│Vendas do produto 2: %d                                      │\n", unitsSoldPonchaB);
    printf("│Vendas do produto 3: %d                                      │\n", unitsSoldPonchaC);
    printf("│Tempo médio de serviço do produto 1: %d                      │\n", avgTimeToServePonchaA);
    printf("│Tempo médio de serviço do produto 2: %d                      │\n", avgTimeToServePonchaB);
    printf("│Tempo médio de serviço do produto 3: %d                      │\n", avgTimeToServePonchaC);
    printf("├─────────────────────────────────────────────────────────────┤\n");

}

void outputMenu() {

}

void pauseShop() {
    //
}

void closeSocket() {
    close(monSocket);
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

            case 's':
                closeSocket();
                halt = 1;
                break;
            
        }

        // e preciso mudar a condicao do while para o op, eventualmente
        // op = getchar();

    } while(halt != 1);

    closeShop();

}

/*

Criação do socket entre o monitor (servidor) e o simulador (cliente).

*/

int client_socket;
struct sockaddr_in monSocketAddress, client;
int lengthStruct = sizeof(struct sockaddr_in);

int TESTstartSocket() {

    // char server_message[256] = "You have reached the server!"; // messageToLog

    // create the server socket
    monSocket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    
    monSocketAddress.sin_family = AF_INET;
    monSocketAddress.sin_port = htons(PORT);
    monSocketAddress.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    if (bind(monSocket, (struct sockaddr*) &monSocketAddress, sizeof(monSocketAddress)) < 0) {
        //printToScreen(logFile, "Erro no bind.\n");
        return -1;
    }

    printf("Bind feito.\n");

    // Listen
    listen(monSocket, 1);

    printf("Listen feito.\n");

    printf("À espera do simulador...\n");

    monSocketConnection = accept(monSocket, (struct sockaddr *) &simSocketAddress, (socklen_t*) &simSocketAddressLength);

    if (monSocketConnection < 0) {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");

    // send the message
    // send(monSocketConnection, server_message, sizeof(server_message), 0);

    // close the socket
    // close(monSocket);

    return monSocketConnection;

}

int outputMonitor;

/* void *recMSG(char* message) {
    while(1) {
        outputMonitor = read(client_socket, messageToLog, strlen(messageToLog));
    }
} */

void *recMSG(void *tid) {

    while(1) {
        //
    }

}

void initThreads() {

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &recMSG, &monSocketConnection);

    //printf("PID do monitor: %d\n", getpid());

}

void monitorRuntime() {

    do {
        //
    } while(op != 'q');

}

void closeShop() {
    printf("A sim terminou\n");

    displayStats();

    close(monSocketConnection);
    close(monSocket);
}


void main() {
    //startServer();


    TESTstartSocket();
    initThreads();

    displayHeader();
    displayMenu();

    monitorRuntime();
    closeShop();
    
    //sendUtilMsg();
    //askForInput();

    
    //stopServer();
}
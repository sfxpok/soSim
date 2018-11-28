#include "libs.h"
#include "unix.h"

/* int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
char *hello = "Hello from server"; 
 */

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
    printf("│(m)enu - mostra o menu                                       │\n");
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

    int halt = 0;

    do {

        printf("Escreva um comando:\n");
        scanf("%c", &op);

        switch(op) {

            case 'i':
                //initThreads();
                break;
            
            case 'h':
                break;

            case 'q': // to be fixed
                halt = 1;
                break;

            case 'm':
                displayMenu();
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

int startMonitorSocket() {

    // char server_message[256] = "You have reached the server!"; // messageToLog

    if ((monSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("Não deu para criar o socket dude.\n");
    }

    printf("Socket criado dude.\n");

    // define the server address
    bzero((char *)&monSocketAddress, sizeof(monSocketAddress));
    monSocketAddress.sun_family = AF_UNIX;
    strcpy(monSocketAddress.sun_path, UNIXSTR_PATH);
    //monSocketAddress.sun_addr.s_addr = INADDR_ANY;
    monLength = strlen(monSocketAddress.sun_path) + sizeof(monSocketAddress.sun_family);

    unlink(UNIXSTR_PATH);

    // bind the socket to our specified IP and port
    if (bind(monSocket, (struct sockaddr *) &monSocketAddress, monLength) < 0) {
        printf("Bind não feito.\n");
        return -1;
    }

    printf("Bind feito.\n");

    // Listen
    listen(monSocket, 1);
    printf("Listen feito.\n");
    printf("À espera do simulador...\n");

    simSocketAddressLength = sizeof(simSocketAddress);

    // mudar o ultimo arg
    if ((monSocketConnection = accept(monSocket, (struct sockaddr *) &simSocketAddress, &simSocketAddressLength)) < 0) {
        printf("Conexão falhada. ");
        return -1;
    }

    printf("Conexão feita.\n");

    // send the message
    // send(monSocketConnection, server_message, sizeof(server_message), 0);

    // close the socket
    // close(monSocket);

    return 0;

}

int outputMonitor;

/* void *recMSG(char* message) {
    while(1) {
        outputMonitor = read(client_socket, messageToLog, strlen(messageToLog));
    }
} */

void *recMSG(void *tid) {

    int monSocket = *((int *) tid);

    while(1) {
        
        int error = 0;

        do {
            if((outputSuccessful = recv(monSocket, opInt, sizeof(opInt), 0)) <= 0) {
                if(outputSuccessful < 0) {
                    //sleep(2);
                    error = 1;
                    printf("recv error");
                }
            }

            //printf("sim\n");

            switch(opInt) {
                case 1:
                    printf("deu alguma coisa\n");
                    break;
            }

        }while(!error);

    }

}

void initThreads() {

    //printf("prethread\n");

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &recMSG, &monSocketConnection);

    //printf("posthread\n");

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


    startMonitorSocket();
    //printf("fiz socket\n");
    initThreads();

    displayHeader();
    displayMenu();
    
    askForInput();
    closeShop();
    
    //sendUtilMsg();
    //askForInput();

    
    //stopServer();
}
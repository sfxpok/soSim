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

void askForInput() {

    printf("entrei no askforinput\n");

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

    printf("sai do askforinput\n");

    //closeShop();

}

void pastaAskForInput() {
    do
    {
        printf("Escreve um comando: \n");
        fgets(buffer, sizeof(buffer), stdin);
        if (!strcmp(buffer, "menu\n"))
            displayMenu();
        if (!strcmp(buffer, "estatistica\n"))
        {
            //mostra_estatistica();
            printf("stat\n");
        }

        if (!strcmp(buffer, "start\n"))
        {
            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {

                printf("send\n");
                exit(1);
            }
            //tempo_inicio_simulacao = time(NULL);
            printf("start?\n");
        }
        if (!strcmp(buffer, "pause\n"))
        {
            printf("Introduza o comando log para ver o registo da simulacao\n");
            printf("Introduza o comando estatistica para ver as mesmas\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }
        }

        if (!strcmp(buffer, "abre\n")) {
            printf("hey do monitor - abre\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }

        }

        if (!strcmp(buffer, "dummy\n"))
        {
            printf("dummy command\n");

            if (send(newsockfd, buffer, sizeof(buffer), 0) == -1)
            {
                exit(1);
            }

        }
    } while (strcmp(buffer, "quit\n"));
}

/* void monitorRuntime() {

    do {
        //
    } while(op != 'q');

} */

void closeShop() {
    printf("A sim terminou\n");

    displayStats();

    closeSocket();

}

/*

Criação do socket entre o monitor (servidor) e o simulador (cliente).

*/

int startMonitorServerSocket() {

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

/*

Criação do socket entre o monitor (cliente) e o simulador (servidor).

*/

int monLength;

int startMonitorClientSocket() {

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

    if (connect(monSocket, (struct sockaddr *) &monSocketAddress, monLength) < 0) {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");

    // send the message
    // send(monSocketConnection, server_message, sizeof(server_message), 0);

    // close the socket
    // close(monSocket);

    printf("prestes a sair da criação do socket\n");

    return 0;

}

void socketPleaseStart() {

    if ((sockfd=socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("cant open socket stream\n");
    }
		
	serverAddr.sun_family=AF_UNIX;
	strcpy(serverAddr.sun_path, UNIXSTR_PATH);
	lengthServer = strlen(serverAddr.sun_path) + sizeof(serverAddr.sun_family);

	unlink(UNIXSTR_PATH);

	if (bind(sockfd, (struct sockaddr *) &serverAddr, lengthServer) < 0) {
        printf("cant bind local address\n");
    }
		
	listen(sockfd, 1);
	
    int lengthClient = sizeof(clientAddr);

	if ((newsockfd=accept(sockfd, (struct sockaddr *) &clientAddr, &lengthClient)) < 0) {
        printf("accept error\n");
    }
}

int outputMonitor;

/* void *recMSG(char* message) {
    while(1) {
        outputMonitor = read(client_socket, messageToLog, strlen(messageToLog));
    }
} */

void *recMSGServer(void *tid) {

    int sockfd = *((int *) tid);

    while(1) {
        
        int error = 0;

        do {
            if((outputSuccessful = recv(sockfd, opInt, sizeof(opInt), 0)) <= 0) {
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

void closeSocket() {
    close(monSocketConnection);
    close(monSocket);
}

void initThreads() {

    printf("prethread\n");

    pthread_t tMessages;
    pthread_create(&tMessages, NULL, &recMSGServer, &newsockfd);

    printf("posthread\n");

    //printf("PID do monitor: %d\n", getpid());

}

void main() {
    //startServer();


    //startMonitorSocket();
    //startMonitorClientSocket();
    socketPleaseStart();

    //printf("fiz socket\n");
    initThreads();

    displayHeader();
    displayMenu();
    
    //askForInput();
    pastaAskForInput();

    closeShop();
    
    //sendUtilMsg();
    //askForInput();

    
    //stopServer();
}
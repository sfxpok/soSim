#include "libs.h"


int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
char *hello = "Hello from server"; 

int server_socket;

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

    pthread_t tMessages;
    // pthread_create(tMessages, NULL, NULL, NULL);

    printf("PID do monitor: %d\n", getpid());

}

void closeSocket() {
    close(server_socket);
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

int startServer() {

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
/*     valread = read(sockfd, buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , messageToLog , strlen(messageToLog) , 0 ); 
    printf("Message sent\n"); 
    return 0;  */

    return 0;

}

void stopServer() {

    close(sockfd);

}

void sendMessageInSocket() {
    valread = read(sockfd, buffer, 1024); 
    printf("%s\n", buffer); 
    send(sockfd, messageToLog, strlen(messageToLog) , 0 ); 
    printf("Hello message sent\n"); 
}

/*

Criação do socket entre o monitor (servidor) e o simulador (cliente).

*/

int TESTstartSocket() {

    char server_message[256] = "You have reached the server!"; // messageToLog

    // create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address, client;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        //printToScreen(logFile, "Erro no bind.\n");
        return -1;
    }

    printf("Bind feito.\n");

    // Listen
    listen(server_socket, 1);

    printf("Listen feito.\n");

    printf("À espera do simulador...\n");

    int lengthStruct = sizeof(struct sockaddr_in);
    int client_socket = accept(server_socket, (struct sockaddr *) &client, (socklen_t*) &lengthStruct);

    if (client_socket < 0) {
        printf("Conexão falhada.\n");
        return -1;
    }

    printf("Conexão feita.\n");

    // send the message
    // send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    // close(server_socket);

    return client_socket;

}

void main() {
    //startServer();
    //displayHeader();
    //displayMenu();

    TESTstartSocket();
    //askForInput();

    // initThreads();
    //stopServer();
}
// Server UDP

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5001   // Porta per UDP

int main() {

    WSADATA wsa;
    SOCKET serverSocket;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char lettera;
    char risposta[50];
    int num1, num2, risultato;

    // Inizializzazione di WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Creazione della socket UDP
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Impostazione parametri server (IP e porta)
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Binding della socket alla porta
    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));

    printf("Server UDP avviato sulla porta %d\n", PORT);

    while(1) {

        // Ricezione lettera dal client
        recvfrom(serverSocket, &lettera, 1, 0,
                 (struct sockaddr*)&client, &client_len);

        // Controllo della lettera e preparazione della risposta
        if(lettera == 'A' || lettera == 'a') strcpy(risposta, "ADDIZIONE");
        else if(lettera == 'S' || lettera == 's') strcpy(risposta, "SOTTRAZIONE");
        else if(lettera == 'M' || lettera == 'm') strcpy(risposta, "MOLTIPLICAZIONE");
        else if(lettera == 'D' || lettera == 'd') strcpy(risposta, "DIVISIONE");
        else strcpy(risposta, "TERMINE PROCESSO CLIENT");

        // Invio al client della stringa con l'operazione
        sendto(serverSocket, risposta, strlen(risposta)+1, 0,
               (struct sockaddr*)&client, client_len);

        // Se deve terminare, passa al prossimo ciclo
        if(strcmp(risposta, "TERMINE PROCESSO CLIENT") == 0)
            continue;

        // Ricezione dei due interi
        recvfrom(serverSocket, (char*)&num1, sizeof(int), 0,
                 (struct sockaddr*)&client, &client_len);

        recvfrom(serverSocket, (char*)&num2, sizeof(int), 0,
                 (struct sockaddr*)&client, &client_len);

        // Esecuzione operazione secondo la lettera
        switch(lettera) {
            case 'A': case 'a': risultato = num1 + num2; break;
            case 'S': case 's': risultato = num1 - num2; break;
            case 'M': case 'm': risultato = num1 * num2; break;
            case 'D': case 'd': risultato = num2 != 0 ? num1 / num2 : 0; break;
        }

        // Invio del risultato al client
        sendto(serverSocket, (char*)&risultato, sizeof(int), 0,
               (struct sockaddr*)&client, client_len);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

// Client UDP

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5001   // Porta per UDP

int main() {

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char serverName[100];
    char lettera;
    char risposta[50];
    int num1, num2, risultato;
    int server_len = sizeof(server);

    // Inizializzazione di WinSock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Creazione socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Inserimento nome server
    printf("Inserisci nome server (es. localhost): ");
    scanf("%s", serverName);

    // Risoluzione DNS
    struct hostent *he = gethostbyname(serverName);
    if (he == NULL) {
        printf("Errore: impossibile risolvere hostname\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memcpy(&server.sin_addr, he->h_addr, he->h_length);

    // Lettura lettera dall'utente
    printf("Inserisci una lettera: ");
    scanf(" %c", &lettera);

    // Invio della lettera al server
    sendto(sock, &lettera, 1, 0,
           (struct sockaddr*)&server, server_len);

    // Ricezione della stringa dal server
    recvfrom(sock, risposta, 50, 0,
             (struct sockaddr*)&server, &server_len);

    // Stampa stringa ricevuta
    printf("%s\n", risposta);

    // Controllo se terminare
    if(strcmp(risposta, "TERMINE PROCESSO CLIENT") == 0) {
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    // Lettura due interi dall'utente
    printf("Inserisci due interi: ");
    scanf("%d %d", &num1, &num2);

    // Invio dei due interi al server
    sendto(sock, (char*)&num1, sizeof(int), 0,
           (struct sockaddr*)&server, server_len);

    sendto(sock, (char*)&num2, sizeof(int), 0,
           (struct sockaddr*)&server, server_len);

    // Ricezione del risultato
    recvfrom(sock, (char*)&risultato, sizeof(int), 0,
             (struct sockaddr*)&server, &server_len);

    // Visualizzazione risultato
    printf("Risultato = %d\n", risultato);

    closesocket(sock);
    WSACleanup();
    return 0;
}

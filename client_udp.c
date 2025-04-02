/*
* Code du client
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define SIZE 100
#define PORT 9600

int main (int argc, char *argv[])
{
    /*
    * Variables du client
    *
    * Déclarer ici les variables suivantes :
    * - sockfd le descripteur de socket
    * - structure d’adresse du serveur
    * - pointeur vers la structure descriptive de machine (hostent)
    * - zone de mémoire destinée à accueillir la chaîne
    * entrée au clavier
    * - taille de la chaîne à envoyer
    */

    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *info_serveur;
    char buffer[SIZE];
    int size_mess;

    /* Ouvrir le socket du client*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Erreur lors de la création du socket");
    }

    /*Récupérer l’adresse IP du serveur à partir de son nom
    * donné en ligne de commande*/
    info_serveur = gethostbyname(argv[1])
    if (server_info == NULL) {
        printf(stderr, "Erreur: hôte inconnu\n");    
    }

    /*Remplir la structure d’adresse du serveur*/
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server_info->h_addr, (char *)&server_addr.sin_addr.s_addr, server_info->h_length);
    server_addr.sin_port = htons(PORT);

    /*Lire une ligne de l’entrée standard*/
    for (int i = 0; i < SIZE; i++) {
        buffer[i] = getchar();
    }

    /*Envoyer la chaîne lue au serveur*/
    size_mess = sendto(sockfd, buffer, strlen(buffer), 0, (struct sokaddr *)&server_addr, sizeof(server_addr))
    if (message_size < 0) {
        printf("Erreur lors de l'envoi du message");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    close(sockfd);

    printf("Message envoyé!");


    return 0;
}
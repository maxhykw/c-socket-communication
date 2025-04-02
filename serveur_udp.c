#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

/* Port local du serveur */
#define PORT 9600

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // le descripteur de socket

    if (sockfd == -1) 
    {
        perror("Erreur lors de la création du socket !");
        return 1;
    }
    
    struct sockaddr_in server_addr;             // structure d’adresse locale du serveur
    struct sockaddr_in client_addr;             // structure d’adresse du client
    socklen_t client_len = sizeof(client_addr); // taille de l’adresse du client
    

    // Remplir la structure d’adresse locale du serveur :
    server_addr.sin_family = AF_INET;         // la famille d’adresse
    server_addr.sin_addr.s_addr = INADDR_ANY; // l'adresse IP 
    server_addr.sin_port = htons(PORT);       // le port


    // Spécifier l'adresse locale du socket du serveur
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) 
    {
        perror("Erreur lors de la liaison du socket !");
        close(sockfd);
        return 1;
    }


    char buffer[21]; // pour stocker la chaîne de caractères du client

    /*
    * Boucle générale du serveur (infinie)
    */
    while (1) {
        // Réception de la chaîne de caractères du client
        ssize_t received_bytes = recvfrom(sockfd, 
                                          buffer, 
                                          sizeof(buffer)-1,
                                          0, 
                                          (struct sockaddr *) &client_addr,
                                          &client_len);

        if (received_bytes == -1) {
            perror("Erreur lors de la réception des données !");
            continue; 
        }

        // Ajouter le caractère de fin de chaîne pour terminer la chaîne reçue
        buffer[received_bytes] = '\0';

        // Afficher la chaîne de caractères du client  
        printf("Message reçu du client: %s\n", buffer);
    }

    // .. sans oublier de fermer le socket du serveur
    close(sockfd);

    return 0;
}
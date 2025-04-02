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
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // le descripteur de socket

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

    // On met le serveur en écoute de connexions
    if (listen(sockfd, 5) == -1)
    {
        perror("Erreur lors de la mise en écoute du socket !");
        close(sockfd);
        return 1;
    }

    printf("Le serveur attend des connexions sur le port %d...\n", PORT);

    // pour gérer la communication avec un client spécifique
    int newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
    
    if (newsockfd == -1)
    {
        perror("Erreur lors de l'acceptation de la connexion !");
        close(sockfd);
        return 1;
    }

    char buffer[21]; // Pour stocker la chaîne de caractères du client

    /*
    * Boucle générale du serveur (infinie)
    */
    while (1)
    {
        // Réception de la chaîne de caractères du client
        ssize_t received_bytes = recv(newsockfd, buffer, sizeof(buffer) - 1, 0);

        if (received_bytes <= 0)
        {
            if (received_bytes == 0)
            {
                printf("La connexion a été fermée par le client.\n");
            }
            else
            {
                perror("Erreur lors de la réception des données !");
            }
            break;
        }

        // Ajouter le caractère de fin de chaîne pour terminer la chaîne reçue
        buffer[received_bytes] = '\0';

        // Afficher la chaîne de caractères du client
        printf("Message reçu du client: %s\n", buffer);
    }

    // .. et on ferme les descripteurs de socket
    close(newsockfd);
    close(sockfd);

    return 0;
}

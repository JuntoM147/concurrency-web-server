#include "server_addr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main() {
        // Create server address
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);       // Ensure big endian
        inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);         // sets the address

        // Creating socket
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket < 0) {
                fprintf(stderr, "Failed to create socket\n");
                exit(EXIT_FAILURE);
        }

        // Connect to server
        int conn_status = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if (conn_status < 0) {
                fprintf(stderr, "Failed to connect\n");
                exit(EXIT_FAILURE);
        }

        printf("Connected to server!\n");
        char msg[64];

        printf("Please write your message to the server: \n");
        fgets(msg, 64, stdin);

        printf("Your message to the server is %s\n", msg);

        write(client_socket, msg, 64);

        if (close(client_socket) < 0) {
                fprintf(stderr, "Failed to close socket file descriptor\n");
                exit(EXIT_FAILURE);
        }

        return 0;
}


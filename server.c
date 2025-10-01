#include "server_addr.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_socklen_t.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
        
        // Create socket
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (server_socket < 0) {
                fprintf(stderr, "Failed to create socket \n");
                exit(EXIT_FAILURE);
        }

        // Bind
        if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                fprintf(stderr, "Failed to bind\n");
                exit(EXIT_FAILURE);
        }

        // Listen
        if (listen(server_socket, 1) < 0) {
                fprintf(stderr, "Failed to listen\n");
                exit(EXIT_FAILURE);
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        char buffer[1024];
        char *msg = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 12\r\n"
                "\r\n"
                "Hello World!";
        
        while (1) {
                int new_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);

                read(new_socket, buffer, 1024);
                printf("Recieved: %s\n", buffer);
                write(new_socket, msg, strlen(msg));
        }

        if (close(server_socket) < 0) {
                fprintf(stderr, "Failed to close socket\n");
                exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main() {
        // Create server address
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(1234);       // Ensure big endian
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);         // sets the address

        // Creating socket
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
                fprintf(stderr, "Failed to create socket\n");
                exit(EXIT_FAILURE);
        }

        // Connect to server
        int conn_status = connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if (conn_status < 0) {
                fprintf(stderr, "Failed to connect\n");
                exit(EXIT_FAILURE);
        }

        printf("Connected to server!\n");

        if (close(socket_fd) < 0) {
                fprintf(stderr, "Failed to close socket file descriptor\n");
                exit(EXIT_FAILURE);
        }

        return 0;
}


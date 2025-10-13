#include "server_addr.h"
#include "handle_conn/handler.h"
#include "queue/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

void *worker(void *arg) {
        int socket = * (int *) arg;
        free(arg);
        handle_connection(socket);
        close(socket);
        return NULL;
}


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
        if (listen(server_socket, 8) < 0) {
                fprintf(stderr, "Failed to listen\n");
                exit(EXIT_FAILURE);
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Create thread pool
        pthread_t thread_pool[8];

        // Create queue
        queue *requests = queue_init();

        // Main loop
        while (1) {
                int *new_socket = malloc(sizeof(int));
                *new_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
                pthread_create(&thread, NULL, worker, new_socket);
                pthread_detach(thread);
        }

        if (close(server_socket) < 0) {
                fprintf(stderr, "Failed to close socket\n");
                exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
}


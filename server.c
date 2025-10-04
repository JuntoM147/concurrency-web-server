#include "server_addr.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_socklen_t.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int parse_request(char *input, char *method, char *path, char*version)
{
        sscanf(input, "%s %s %s", method, path, version);
        return 0;
}

void write_response(const char *filename, int socket) {
        FILE *fptr;
        fptr = fopen(filename, "r");

        if (fptr == NULL) {
                write(
                        socket,
                        "HTTP/1.1 404 Not found\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 62\r\n"
                        "\r\n"
                        "<!DOCTYPE HTML><html><body><h1>404 not found</h1></body></html>",
                       138 
                );
                return;
        }

        // Get file size
        fseek(fptr, 0L, SEEK_END);
        long sz = ftell(fptr);
        rewind(fptr);

        char header[256];

        int header_len = snprintf(
                header,
                sizeof(header),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: %ld\r\n"
                "\r\n",
                sz
        );

        write(socket, header, header_len);

        char filebuff[1024];
        int chars_read;

        while ((chars_read = fread(filebuff, sizeof(char), 1024, fptr)) > 0) {
                write(socket, filebuff, chars_read);
        }

        fclose(fptr);
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
        if (listen(server_socket, 1) < 0) {
                fprintf(stderr, "Failed to listen\n");
                exit(EXIT_FAILURE);
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        char request[1024];
        char *msg;
        char method[8], path[64], version[16];
        
        while (1) {
                int new_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);

                read(new_socket, request, 1024);

                parse_request(request, method, path, version);

                if (strcmp(path, "/") == 0) {
                        write_response("index.html", new_socket);
                } else if (strcmp(path, "/hello") == 0) {
                        msg = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: 12\r\n"
                                "\r\n"
                                "Hello World!";
                        write(new_socket, msg, strlen(msg));
                } else {
                        msg = "HTTP/1.1 404 Not found\r\n" 
                        "Content-Type: text/html\r\n"
                        "Content-Length: 62\r\n"
                        "\r\n"
                        "<!DOCTYPE HTML><html><body><h1>404 not found</h1></body></html>";
                        write(new_socket, msg, strlen(msg));
                }
        }

        if (close(server_socket) < 0) {
                fprintf(stderr, "Failed to close socket\n");
                exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
}


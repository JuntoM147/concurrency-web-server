#include "send_error.h"
#include <unistd.h>

void send_error(int socket, enum error_code err) {
        switch (err) {
        case not_found:
                write(
                        socket,
                        "HTTP/1.1 404 Not found\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 62\r\n"
                        "\r\n"
                        "<!DOCTYPE HTML><html><body><h1>404 Not Found</h1></body></html>",
                       138 
                );
        case internal_server_error:
                write(
                        socket,
                        "HTTP/1.1 500 Internal Server Error\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 70\r\n"
                        "\r\n"
                        "<!DOCTYPE HTML><html><body><h1>Internal Server Error</h1></body></html>",
                       154 
                );
        case bad_request:
                write(
                        socket,
                        "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 64\r\n"
                        "\r\n"
                        "<!DOCTYPE HTML><html><body><h1>Bad Request</h1></body></html>",
                       142 
                );
        }
}


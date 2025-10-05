#include "handler.h"
#include "parser.h"
#include "extract_path.h"
#include "send_error.h"
#include "serve_file.h"
#include <stdio.h>
#include <unistd.h>

void epilogue(int socket) {
        if (close(socket) < 0) {
                fprintf(stderr, "Failed to close socket\n");
        }
}


void handle_connection(int socket) {
        // Read request
        char raw_request[1024];
        read(socket, raw_request, 1024);

        // Parse request
        struct req_header header;

        if(parse_request(raw_request, &header) != 0) {
                send_error(socket, internal_server_error);
                epilogue(socket);
                return;
        }

        // Extract filepath
        char path[MAX_PATH_LEN];
        if (extract_path(path, &header) != 0) {
                // Invalid / Malicious path
                send_error(socket, bad_request);
        } else {
                // Serve Request
                serve_file(path, socket);
        }

        epilogue(socket);
}


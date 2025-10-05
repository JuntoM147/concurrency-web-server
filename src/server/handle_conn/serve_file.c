#include "serve_file.h"
#include "send_error.h"
#include <unistd.h>
#include <stdio.h>

void serve_file(char *file_path, int socket) {
        FILE *fptr;

        printf("Serving %s\n", file_path);

        fptr = fopen(file_path, "r");

        if (fptr == NULL) {
                send_error(socket, not_found);
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

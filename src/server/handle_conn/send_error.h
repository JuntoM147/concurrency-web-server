#ifndef SEND_ERROR

#define SEND_ERROR

enum error_code {
        not_found,
        internal_server_error,
        bad_request
};

void send_error(int socket, enum error_code err);

#endif

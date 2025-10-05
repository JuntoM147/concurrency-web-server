#ifndef PARSER
#define PARSER

struct req_header {
        char method[8];
        char path[1024];
        char version[16];
};

int parse_request(char *request, struct req_header *header);

#endif


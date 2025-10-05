#include "parser.h"
#include <stdio.h>

int parse_request(char *request, struct req_header *header){
        if (sscanf(request, "%7s %1023s %15s", header->method, header->path, header->version) != 3) {
                return -1;
        }

        return 0;
}

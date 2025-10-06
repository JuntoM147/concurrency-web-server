#include "extract_path.h"
#include <string.h>
#include <stdio.h>

int extract_path(char *path, struct req_header *request) {
        if (strstr(request->path, "..")) {
                printf("Invalid path!\n");
                return -1;
        }

        if (strcmp("/", request->path) == 0) {
                snprintf(path, MAX_PATH_LEN, "%s", "static/index.html");
        } else {
                snprintf(path, MAX_PATH_LEN, "static%s", request->path);
        }

        return 0;
}


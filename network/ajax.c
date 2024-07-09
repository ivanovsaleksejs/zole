#include <fcgi_stdio.h>

#include "ajax.h"

void handle_ajax_request() {
    char *request_uri = getenv("REQUEST_URI");

    if (strstr(request_uri, "/ajax") != NULL) {
        printf("Content-type: application/json\r\n\r\n");
        printf("[");
        printf("{\"name\":\"%s\"}", "test");
        printf("]\n");
    }
}

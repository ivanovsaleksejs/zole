#include <fcgi_stdio.h>
#include <libwebsockets.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#include "network/ajax.h"
#include "network/websockets.h"
#include "libzole/libzole.h"
#include "tests/tests.h"

void test() {
    srand(time(NULL));

    initializeDeck();

    for (int count = 0; count < 100; count++) {
        int result[3];
        threeCards(result);

        int winIndex = winner(result[0], result[1], result[2]);

        dprintf(STDOUT_FILENO, "Trick: %s %s %s", deck[result[0]], deck[result[1]], deck[result[2]]);
        dprintf(STDOUT_FILENO, " The winner is %d (%s)\n", winIndex, deck[result[winIndex]]);
    }
}

void startServer() {
    pthread_t ws_thread;
    pthread_create(&ws_thread, NULL, start_websocket_server, NULL);

    while (FCGI_Accept() >= 0) {
        handle_ajax_request();
    }

    pthread_join(ws_thread, NULL);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        test();
    } else {
        startServer();
    }

    return 0;
}

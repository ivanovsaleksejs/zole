#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "libzole/libzole.h"
#include "tests/tests.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        srand(time(NULL));

        initializeDeck();

        for (int count = 0; count < 20; count++) {
            int result[3];
            threeCards(result);

            int winIndex = winner(result[0], result[1], result[2]);

            printf("Galds: %s, %s, %s", deck[result[0]], deck[result[1]], deck[result[2]]);
            printf(" Uzvar: %s\n", deck[result[winIndex]]);
        }
    } else {
        printf("Nothing here\n");
    }

    return 0;
}

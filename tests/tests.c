#include <stddef.h>
#include <stdlib.h>

#include "tests.h"

void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void threeCards(int *result) {
    int temp[25];
    int i, k = 0;

    for (i = 0; i < 12; i++) {
        temp[k++] = i + i / 3;
    }

    for (i = 0; i < 14; i++) {
        temp[k++] = i + 16;
    }

    shuffle(temp, 26);

    for (i = 0; i < 3; i++) {
        result[i] = temp[i];
    }
}

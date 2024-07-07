#include <stddef.h>

#include "libzole.h"

const char *trumps[] = {
    "\033[0;31m 7♦\033[0m",
    "\033[0;31m 8♦\033[0m",
    "\033[0;31m 9♦\033[0m",
    "\033[0;31m K♦\033[0m",
    "\033[0;31m10♦\033[0m",
    "\033[0;31m A♦\033[0m",
    "\033[0;31m J♦\033[0m",
    "\033[0;31m J♥\033[0m",
    " J♠",
    " J♣",
    "\033[0;31m Q♦\033[0m",
    "\033[0;31m Q♥\033[0m",
    " Q♠",
    " Q♣"
};

const char *extras[] = {
  " 9♣", " 9♠", "\033[0;31m 9♥\033[0m", "",
  " K♣", " K♠", "\033[0;31m K♥\033[0m", "",
  "10♣", "10♠", "\033[0;31m10♥\033[0m", "",
  " A♣", " A♠", "\033[0;31m A♥\033[0m", "",
};

const char *deck[sizeof(extras) / sizeof(extras[0]) + sizeof(trumps) / sizeof(trumps[0])];

void initializeDeck() {
    size_t i, j = 0;
    for (i = 0; i < sizeof(extras) / sizeof(extras[0]); i++) {
        deck[j++] = extras[i];
    }
    for (i = 0; i < sizeof(trumps) / sizeof(trumps[0]); i++) {
        deck[j++] = trumps[i];
    }
}

int getColor(int n) {
    return n & 3 | n >> 4 << 1 | n >> 4;
}

int maxOf3(int a, int b, int c) {
    return (c > a & c > b) << 1 | (b > a & b > c);
}

int transform(int n, int color) {
    return n & -(n >> 4 | (n & 3) == color);
}

int winner(int a, int b, int c) {
    int color = getColor(a);
    return maxOf3(a, transform(b, color), transform(c, color));
}

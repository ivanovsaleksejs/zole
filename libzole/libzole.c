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

int winner(int a, int b, int c) {
    int t(int n) {
        return n & -(n >> 4 | n % 4 == a % 4);
    }
    return ((c = t(c)) > a | ((b = t(b)) > a)) << (c > b);
}

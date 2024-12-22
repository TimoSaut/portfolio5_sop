#include "wc_functions.h"
#include <stdio.h>
#include <stdbool.h>

int count_lines(FILE *file) {
    int lines = 0;
    char c;
    while ((c = getc(file)) != EOF) { //EOF sollte für End of File stehen.
        if (c == '\n') {
            lines++;
        }
    }
    return lines;
}

int count_words(FILE *file) {
    int words = 0;
    char c;
    bool in_word = false;
    while ((c = getc(file)) != EOF) {
        if (c == ' ') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            words++;
        }
    }
    return words;
}

int count_characters(FILE *file) {
    int letters = 0;
    while (fgetc(file) != EOF) {
        letters++;
    }
    return letters;
}

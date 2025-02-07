#include "wc_functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int count_lines(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Fehler beim Öffnen der Datei");
        return -1;
    }

    int lines = 0;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                lines++;
            }
        }
    }

    close(fd);
    return lines;
}

int count_words(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Fehler beim Öffnen der Datei");
        return -1;
    }

    int words = 0;
    bool in_word = false;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                in_word = false;
            } else if (!in_word) {
                in_word = true;
                words++;
            }
        }
    }

    close(fd);
    return words;
}

int count_characters(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Fehler beim Öffnen der Datei");
        return -1;
    }

    int characters = 0;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        characters += bytes_read;
    }

    close(fd);
    return characters;
}

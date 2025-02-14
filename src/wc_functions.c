#include "wc_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void process_file_or_stdin(const char *filename, FileStats *stats) {
    if (stats == NULL) {
        fprintf(stderr, "Fehler: Ungültiger Zeiger auf FileStats\n");
        return;
    }

    int fd;
    if (filename == NULL || strcmp(filename, "-") == 0) {
        fd = STDIN_FILENO;
    } else {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Fehler beim Öffnen der Datei");
            return;
        }
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int current_length = 0;
    bool in_word = false;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            stats->characters++;

            if (buffer[i] == '\n') {
                stats->lines++;
                if (in_word) {
                    stats->words++;
                    in_word = false;
                }
                if (current_length > stats->longest_line) {
                    stats->longest_line = current_length;
                }
                current_length = 0;
            } else {
                current_length++;
            }

            if (isspace(buffer[i])) {
                in_word = false;
            } else if (!in_word) {
                in_word = true;
                stats->words++;
            }
        }
    }

    if (current_length > stats->longest_line) {
        stats->longest_line = current_length;
    }

    if (stats->characters == 0) {
        stats->longest_line = 0;
    }

    if (fd != STDIN_FILENO && fd != -1) {
        if (close(fd) == -1) {
            perror("Fehler beim Schließen der Datei");
        }
    }
}

void *thread_process_file(void *arg) {
    if (arg == NULL) {
        fprintf(stderr, "Fehler: ThreadData-Zeiger ist NULL\n");
        return NULL;
    }

    ThreadData *data = (ThreadData *) arg;

    if (data->filename == NULL || data->stats == NULL) {
        fprintf(stderr, "Fehler: Ungültige ThreadData-Struktur\n");
        return NULL;
    }

    process_file_or_stdin(data->filename, data->stats);
    return NULL;
}

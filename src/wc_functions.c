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
        if (bytes_read == -1) {

            perror("Fehler beim Lesen der Datei");
            if (fd != STDIN_FILENO) {
                close(fd);
            }
            return;
        }

        for (ssize_t i = 0; i < bytes_read; i++) {
            stats->characters++;

            if (buffer[i] == '\n') {
                stats->lines++;
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


    if (fd != STDIN_FILENO) {
        if (close(fd) == -1) {

            perror("Fehler beim Schließen der Datei");
        }
    }
}

void *thread_process_file(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    process_file_or_stdin(data->filename, data->stats);
    return NULL;
}

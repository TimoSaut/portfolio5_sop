#include "wc_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

// Datei oder stdin und struct füllen
void process_file_or_stdin(const char *filename, FileStats *stats) {
    int fd;
    if (filename == NULL) {
        fd = STDIN_FILENO; // stdin wenn kein Name gegeben
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
            stats->characters++;  // Zeichen zählen

            if (buffer[i] == '\n') {
                stats->lines++;  // Zeilen zählen
                if (current_length > stats->longest_line) {
                    stats->longest_line = current_length;
                }
                current_length = 0;  // Länge der neuen Zeile starten
            } else {
                current_length++;
            }

            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                in_word = false;
            } else if (!in_word) {
                in_word = true;
                stats->words++;  // Wort erkannt
            }
        }
    }

    if (current_length > stats->longest_line) {
        stats->longest_line = current_length;
    }

    if (fd != STDIN_FILENO) {
        close(fd);
    }
}

// Thread für gleichzeitiges Datei-Lesen
void *thread_process_file(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    pthread_mutex_lock(data->mutex);
    process_file_or_stdin(data->filename, data->stats);
    pthread_mutex_unlock(data->mutex);

    return NULL;
}


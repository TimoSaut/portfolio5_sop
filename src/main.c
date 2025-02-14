#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "wc_functions.h"

pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

void help() {
    printf("Verwendung: wc_program [OPTION]... [DATEI]...\n");
    printf("Zählt Zeilen, Wörter, Zeichen und maximale Zeilenlänge in DATEI(en) oder stdin.\n\n");
    printf("Optionen:\n");
    printf("  -l        Zeilen zählen\n");
    printf("  -w        Wörter zählen\n");
    printf("  -m        Zeichen zählen\n");
    printf("  -L        Längste Zeile anzeigen\n");
    printf("  -h        Menschenlesbare Ausgabe\n");
    printf("  --help    Diese Hilfe anzeigen\n");
}

int beginsWithLine(char arr[]) {
    return arr[0] == '-';
}

void parse_args(int argc, char *argv[],
                char ***files, int *file_count,
                int *lines, int *words, int *chars,
                int *max_line, int *human_readable,
                int *help_flag) {
    *file_count = 0;
    *files = malloc(argc * sizeof(char *));
    int no_flag = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            *help_flag = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            *lines = 1;
            no_flag = 0;
        } else if (strcmp(argv[i], "-w") == 0) {
            *words = 1;
            no_flag = 0;
        } else if (strcmp(argv[i], "-m") == 0) {
            *chars = 1;
            no_flag = 0;
        } else if (strcmp(argv[i], "-L") == 0) {
            *max_line = 1;
            no_flag = 0;
        } else if (strcmp(argv[i], "-h") == 0) {
            *human_readable = 1;
        } else if (!beginsWithLine(argv[i])) {
            (*files)[(*file_count)++] = argv[i];
        } else {
            fprintf(stderr, "Unbekannte Option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (no_flag) {
        *lines = *words = *chars = *max_line = 1;
    }

    if (*file_count == 0) {
        (*files)[(*file_count)++] = "-";
    }
}

void print_stats(ThreadData *data) {
    pthread_mutex_lock(&output_mutex);

    const char *name = strcmp(data->filename, "-") == 0
                           ? "stdin"
                           : data->filename;

    if (!data->stats->file_found) {
        printf("Datei %s nicht gefunden!\n", name);
        pthread_mutex_unlock(&output_mutex);
        return;
    }

    if (data->stats->lines == 0 && data->stats->words == 0) {
        printf("Datei %s ist leer!\n", name);
        pthread_mutex_unlock(&output_mutex);
        return;
    }

    if (data->human_readable) {
        printf("\nDatei: %s\n", name);
        if (data->lines) printf("Zeilen: %d\n", data->stats->lines);
        if (data->words) printf("Wörter: %d\n", data->stats->words);
        if (data->chars) printf("Zeichen: %d\n", data->stats->characters);
        if (data->max_line) printf("Längste Zeile: %d\n", data->stats->longest_line);
    } else {
        if (data->lines) printf("%d ", data->stats->lines);
        if (data->words) printf("%d ", data->stats->words);
        if (data->chars) printf("%d ", data->stats->characters);
        if (data->max_line) printf("%d ", data->stats->longest_line);
        if (strcmp(name, "stdin") != 0)printf("%s\n", name);
    }

    pthread_mutex_unlock(&output_mutex);
}

void *process_file_thread(void *arg) {
    ThreadData *data = (ThreadData *) arg;

    process_file_or_stdin(
        strcmp(data->filename, "-") == 0 ? NULL : data->filename,
        data->stats
    );

    print_stats(data);
    return NULL;
}

int main(int argc, char *argv[]) {
    char **files = NULL;
    int file_count = 0;
    int lines = 0, words = 0, chars = 0, max_line = 0;
    int human_readable = 0, help_flag = 0;

    parse_args(argc, argv, &files, &file_count,
               &lines, &words, &chars, &max_line,
               &human_readable, &help_flag);

    if (help_flag) {
        help();
        free(files);
        return 0;
    }

    pthread_t *threads = malloc(file_count * sizeof(pthread_t));
    ThreadData *thread_data = malloc(file_count * sizeof(ThreadData));
    FileStats *stats = malloc(file_count * sizeof(FileStats));

    for (int i = 0; i < file_count; i++) {
        thread_data[i] = (ThreadData){
            .filename = files[i],
            .stats = &stats[i],
            .mutex = &output_mutex,
            .lines = lines,
            .words = words,
            .chars = chars,
            .max_line = max_line,
            .human_readable = human_readable
        };
        pthread_create(&threads[i], NULL, process_file_thread, &thread_data[i]);
    }

    for (int i = 0; i < file_count; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(thread_data);
    free(stats);
    free(files);

    return 0;
}

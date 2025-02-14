#ifndef WC_FUNCTIONS_H
#define WC_FUNCTIONS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>


typedef struct {
    int lines;
    int words;
    int characters;
    int longest_line;
    bool file_found;
} FileStats;


typedef struct {
    const char *filename;
    FileStats *stats;
    pthread_mutex_t *mutex;
    int lines, words, chars, max_line, human_readable;
} ThreadData;


void process_file_or_stdin(const char *filename, FileStats *stats);

void *thread_process_file(void *arg);

#endif // WC_FUNCTIONS_H

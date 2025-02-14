#ifndef MAIN_H
#define MAIN_H



void parse_args(int argc, char *argv[],
                char ***files, int *file_count,
                int *lines, int *words, int *chars,
                int *max_line, int *human_readable,
                int *help_flag);

#endif

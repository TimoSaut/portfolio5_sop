#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "wc_functions.h"


void help(){
        printf("With no FILE, or when FILE is -, read standard input.\n\n");
        printf("The options below may be used to select which counts are printed, always in\n");
        printf("the following order: newline, word, character, maximum line length.\n");
        printf("  -m: (chars)            -> print the character counts\n");
        printf("  -l: (lines)            -> print the newline counts\n");
        printf("      (files0-from=F)    -> read input from the files specified by\n");
        printf("                             NUL-terminated names in file F;\n");
        printf("                             If F is - then read names from standard input\n");
        printf("  -L: (max_line_length)  -> print the maximum display width\n");
        printf("  -w: (words)            -> print the word counts\n");
        printf("      --help     -> display this help and exit\n");
        printf("      --version  -> output version information and exit\n\n");
       // printf("GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n");
        //printf("Report any translation bugs to <https://translationproject.org/team/>\n");
       // printf("Full documentation <https://www.gnu.org/software/coreutils/wc>\n");
      //  printf("or available locally via: info '(coreutils) wc invocation'\n");
    }

void parse_args(int argc, char *argv[]) {

    int no_flag = 0;
    int lines = 0;
    int words = 0;
    int chars = 0;
    int max_line = 0;
    int human_readable = 0;
    int help_flag = 0;

    if (argc == 2) {
        no_flag = 1;
    }





    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            lines = 1;
        } else if (strcmp(argv[i], "-w") == 0) {
            words = 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            chars = 1;
        } else if (strcmp(argv[i], "-L") == 0) {
            max_line = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            human_readable = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            help_flag = 1;
        } else if (i < argc - 1){
            printf("Unbekanntes Flag: %s\n", argv[i]);
            exit(1);
        }
    }



    const char *file = argv[argc - 1];
    int c;


    if (human_readable) {
        if (lines) {
            c = count_lines(file);
            printf("File %s includes %i lines.", file, c);
        } if (words) {
            c = count_words(file);
            printf("File %s includes %i words.", file, c);
        }  if (chars) {
            c = count_characters(file);
            printf("File %s includes %i characters.", file, c);
        }  if (max_line) {
            c = count_longest_line(file);
            printf("File %s logest line is line %i.", file, c);
        }
    } else {
        if (lines) {
            c = count_lines(file);
            printf("%i", c);
        }  if (words) {
            c = count_words(file);
            printf("%i", c);
        }  if (chars) {
            c = count_characters(file);
            printf("%i", c);
        }  if (max_line) {
            c = count_longest_line(file);
            printf("%i", c);
        }  if (no_flag) {
            // hier alles ausgeben
        } if (help_flag) {
            help();
        }
    }
}



int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    return 0;
}

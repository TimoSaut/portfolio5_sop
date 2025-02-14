#include <criterion/criterion.h>
#include "../src/main.h"


// Test für Argumentenverarbeitung
Test(WC_Args, ParseArguments) {
    char *argv[] = {"new_wc", "-l", "-w", "-c", "testfile.txt"};
    int argc = 5;

    char **files = NULL;
    int file_count = 0;
    int lines = 0, words = 0, chars = 0, max_line = 0, human_readable = 0, help_flag = 0;

    parse_args(argc, argv, &files, &file_count, &lines, &words, &chars, &max_line, &human_readable, &help_flag);

    cr_assert_eq(lines, 1, "Option '-l' wurde nicht erkannt!");
    cr_assert_eq(words, 1, "Option '-w' wurde nicht erkannt!");
    cr_assert_eq(chars, 1, "Option '-c' wurde nicht erkannt!");
    cr_assert_eq(file_count, 1, "Es wurde keine Datei erkannt!");

    free(files);
}

#include <criterion/criterion.h>
#include "../src/wc_functions.h"
#include <stdio.h>

// Test für Zeichen-, Wort- und Zeilenzählung
Test(WC_Functions, CountCharactersWordsLines) {
    FileStats stats = {0, 0, 0, 0};
    char *test_text = "Hello World!\nThis is a test.\n";

    // Testdatei erstellen
    FILE *fp = fopen("test_input.txt", "w");
    fputs(test_text, fp);
    fclose(fp);

    process_file_or_stdin("test_input.txt", &stats);

    cr_assert_eq(stats.lines, 2, "Erwartete 2 Zeilen, aber bekam %d", stats.lines);
    cr_assert_eq(stats.words, 5, "Erwartete 5 Wörter, aber bekam %d", stats.words);
    cr_assert_eq(stats.characters, 30, "Erwartete 30 Zeichen, aber bekam %d", stats.characters);
}

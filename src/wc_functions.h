//
// Created by damok on 21.12.2024.
//

#ifndef WC_FUNCTIONS_H
#define WC_FUNCTIONS_H

#include <sys/types.h>  // Für `ssize_t`
#include <sys/stat.h>   // Für `open()` Flags
#include <fcntl.h>      // Für `open()`
#include <unistd.h>     // Für `read()` und `close()`
#include <stdbool.h>    // Für `bool`

// Funktionen für Wort-, Zeichen- und Zeilenzählung
int count_lines(const char *filename);
int count_words(const char *filename);
int count_characters(const char *filename);

#endif //WC_FUNCTIONS_H

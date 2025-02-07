#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "wc_functions.h"

void parse_args(int argc, char *argv[]) {
    if (argc < 3) {
        printf("FEHLER: bitte beachte den korrekten Aufruf");
        //hier --help noch mit ausgeben
        return;
    }


    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("--help erkannt\n");
        } else {
            // const char *file = argv[2];
            FILE *filename = fopen(argv[2], "r");
            if (filename == NULL) {
                printf("FEHLER: Datei konnte nicht geöffnet werden: %s\n", argv[2]);
                return;
            }

            switch (argv[i][1]) {
                case 'c':
                    printf("C erkannt");
                    i = count_lines(filename);
                    printf("%i", i);
                    break;
                case 'w':
                    printf("w erkannt");
                    break;
                case 'l':
                    printf("l erkannt");
                    break;
                case 'L':
                    printf("L erkannt");
                    break;
                case 'h':
                    printf("h erkannt");
                    break;
                default:
                    printf("default case flag nicht gefunden");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    return 0;
}

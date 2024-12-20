#include <string.h>
#include <stdio.h>

void parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            printf("Flag '-c' erkannt\n");
        }
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    return 0;
}

#include <string.h>
#include <stdio.h>

void parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--help") == 0){
        printf("--help erkannt");
        }else if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'c':
                    printf("C erkannt");
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
                case '-help':
                    printf("-help erkannt");
                    break;
            }
        } else {
                printf("default case flag nicht gefunden");
        }
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    return 0;
}
